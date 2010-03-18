/*	Copyright (C) 2005 Simon David Rycroft

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. */

import com.sun.java.browser.net.ProxyInfo;
import com.sun.java.browser.net.ProxyService;
import java.io.File;
import java.io.FileInputStream;
import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.net.Socket;
import java.net.URL;
import java.util.Random;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;
import javax.net.ssl.SSLContext;

import java.net.UnknownHostException;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.io.UnsupportedEncodingException;

import java.io.InputStream;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.io.ByteArrayOutputStream;
import java.io.ByteArrayInputStream;

public class UploadThread extends Thread{

	private File file;
	private Main main;
	private int attempts, finalByteSize;
	private static final String lotsHyphens="---------------------------";
	private static final String lineEnd="\r\n";
	private String header, footer, request, reply, afterContent;
	private InputStream fileStream;
	private URL url;
	private String boundary;
	private Socket sock;
	private boolean addPngToFileName;
	private boolean doUpload;

	public UploadThread(URL u, File f, Main m) throws IOException, UnknownHostException{

		url = u;
		file = f;
		main = m;
		attempts = 0;
		doUpload = true;
	}

	public void run(){
		try {
			upload();
		}
		catch (FileNotFoundException fnfe) {
			// A file has been moved or deleted. This file will NOT
			// be uploaded.
			// Set the progress to include this file.
			main.fileNotFound(file);
			main.setProgress((int)file.length());
		}
		catch (IOException ioe){
			// No idea what could have caused this, so simply call this.run() again.
			this.run();
			// This could end up looping. Probably need to find out what could cause this.
			// I guess I could count the number of attempts!
			main.errorMessage("IOException: UploadThread");
		}
	}

	public void cancelUpload(){
		doUpload = false;
	}
	private void upload() throws FileNotFoundException, IOException{

		this.uploadFile();
		// Check to see if the file was uploaded
		if (reply != null && reply.indexOf("POSTLET:NO")>0) {
			if (reply.indexOf("POSTLET:RETRY")>0){
				reply = "";
				if (attempts<3) {
					main.setProgress(-(int)file.length());
					main.setProgress(finalByteSize); // Has to be added after whole file is removed.
					attempts++;
					this.upload();
				}
				else {
					main.fileUploadFailed(file);
					main.setProgress(finalByteSize);
				}
			} else {
				if(reply.indexOf("POSTLET:FILE TYPE NOT ALLOWED")>0){
					main.fileNotAllowed(file);
				}
				else {
					main.fileUploadFailed(file);
				}
				attempts = 5;
				main.setProgress(finalByteSize);
			}
		}
		else {
			// Set the progress, that this file has uploaded.
			main.addUploadedFile(file);
			main.setProgress(finalByteSize);
		}
	}

	private synchronized void uploadFile() throws FileNotFoundException, IOException{

		// Get the file stream first, as this is needed for the content-length
		// header.
		this.setInputStream();
		
		sock = getSocket();

		this.setBoundary(40);
		this.setHeaderAndFooter();
		// Output stream, for writing to the socket.
		DataOutputStream output = new DataOutputStream(new BufferedOutputStream(sock.getOutputStream()));
		// Reader for accepting the reply from the server.
		BufferedReader input = new BufferedReader(new InputStreamReader(sock.getInputStream()));

		// Write the request, and the header.
		output.writeBytes(request);
		try {
			output.write(header.getBytes("UTF-8")); }// Write in UTF-8! - May change all
		catch (UnsupportedEncodingException uee){
			// Just ignore this error, and instead write out the bytes without
			// getting as UTF-8!
			main.errorMessage("Couldn't get header in UTF-8");
			output.writeBytes(header);
		}

		output.flush();

		// Create a ReadLine thread to read the possible output.
		// Possible catching of errors here if the return isn't 100 continue
		ReadLine rl = new ReadLine(input, this);
		rl.start();
		try {
			// Should be dynamically setting this.
			wait(1000);
		}
		catch (InterruptedException ie){
			// Thread was interuppted, which means there was probably
			// some output!
		}
		output.writeBytes(afterContent);
		// Debug: Show that the above has passed!

		// Following reads the file, and streams it.
		/////////////////////////////////////////////////////////////
		//FileInputStream fileStream = new FileInputStream(file);
		int numBytes = 0;

		if (file.length()>Integer.MAX_VALUE){
			throw new IOException("*** FILE TOO BIG ***");
		}

		// Size of buffer - May need reducing if users encounter
		// memory issues.
		int maxBufferSize = 1024;
		int bytesAvailable = fileStream.available();
		int bufferSize = Math.min(bytesAvailable,maxBufferSize);
		finalByteSize = 0; // Needs to be passed to the upload method!

		byte buffer [] = new byte[bufferSize];

		int bytesRead = fileStream.read(buffer, 0, bufferSize);
		while (bytesAvailable > 0 && doUpload)
		{
			output.write(buffer, 0, bufferSize);
			if (bufferSize == maxBufferSize)
				main.setProgress(bufferSize);
			else
				finalByteSize = bufferSize;
			bytesAvailable = fileStream.available();
			bufferSize = Math.min(bytesAvailable,maxBufferSize);
			bytesRead = fileStream.read(buffer, 0, bufferSize);
		}
		///////////////////////////////////////////////////////////
		if (doUpload){
			output.writeBytes(footer);
			output.writeBytes(lineEnd);

			output.flush();

			try {
				// Should be dynamically setting this.
				wait(1000);
			}
			catch (InterruptedException ie){
				// Thread was interuppted, which means there was probably
				// some output!
			}
			reply = rl.getRead();
			main.errorMessage("REPLY");
			main.errorMessage(reply);
			main.errorMessage("END REPLY");
		}
		// Close the socket and streams.
		input.close();
		output.close();
		sock.close();
	}

	// Each UploadThread gets a new Socket.
	// This is bad, especially when talking to HTTP/1.1 servers
	// which are able to keep a connection alive. May change this
	// to have the UploadManager create the threads, and reuse them
	// passing them to each of the UploadThreads.
	private Socket getSocket() throws IOException, UnknownHostException{
		if (url.getProtocol().equalsIgnoreCase("https")){
			// Create a trust manager that does not validate certificate chains
			TrustManager[] trustAllCerts = new TrustManager[]{
				new X509TrustManager() {
					public java.security.cert.X509Certificate[] getAcceptedIssuers() {
						return null;
					}
					public void checkClientTrusted(
							java.security.cert.X509Certificate[] certs, String authType) {
					}
					public void checkServerTrusted(
							java.security.cert.X509Certificate[] certs, String authType) {
					}
				}
			};
			// Install the all-trusting trust manager
			try {
				SSLContext sc = SSLContext.getInstance("SSL");
				sc.init(null, trustAllCerts, new java.security.SecureRandom());
				int port = url.getPort();
				if (url.getPort()>0)
					return sc.getSocketFactory().createSocket(url.getHost(),url.getPort());
				else
					return sc.getSocketFactory().createSocket(url.getHost(),443);
			}
			catch (Exception e) {
			}
		}
		else {
			try {
				ProxyInfo info[] = ProxyService.getProxyInfo(url);
				if(info != null && info.length>0){
					String proxyHost = info[0].getHost();
					int proxyPort = info[0].getPort();
					main.errorMessage("PROXY = " + proxyHost + ":" + proxyPort);
					return new Socket(proxyHost, proxyPort);
				}
			}catch (Exception ex) {
				main.errorMessage("could not retrieve proxy configuration, attempting direct connection.");
			}
			Socket s;
			String proxyHost = System.getProperties().getProperty("deployment.proxy.http.host");
			String proxyPort = System.getProperties().getProperty("deployment.proxy.http.port");
			String proxyType = System.getProperties().getProperty("deployment.proxy.type");
			if ( (proxyHost == null || proxyType == null) || (proxyHost.equalsIgnoreCase("") || proxyType.equalsIgnoreCase("0") || proxyType.equalsIgnoreCase("2") || proxyType.equalsIgnoreCase("-1") )){
				if(!main.getProxy().equals("")){
					String proxyParts[] = main.getProxy().split(":");
					try{
						s = new Socket(proxyParts[0],Integer.parseInt(proxyParts[1]));
						main.errorMessage("Proxy (parameter) - "+proxyParts[0]+":"+proxyParts[1]);
					}
					catch (NumberFormatException badPort){
						main.errorMessage("bad proxy parameter");
						if (url.getPort()>0)
							s = new Socket(url.getHost(),url.getPort());
						else
							s = new Socket(url.getHost(),80);						
					}
				}
				if (url.getPort()>0)
					s = new Socket(url.getHost(),url.getPort());
				else
					s = new Socket(url.getHost(),80);
			}
			else{
				// Show when a Proxy is being user.
				main.errorMessage("Proxy (browser) - "+proxyHost+" - "+proxyPort+" - "+proxyType);
				try {
					s = new Socket(proxyHost,Integer.parseInt(proxyPort));}
				catch (NumberFormatException badPort){
					// Probably not a bad idea to try a list of standard Proxy ports
					// here (8080, 3128 ..), then default to trying the final one.
					// This could possibly be causing problems, display of an
					// error message is probably also a good idea.
					main.errorMessage("bad proxy from browser");
					if (url.getPort()>0)
						s = new Socket(url.getHost(),url.getPort());
					else
						s = new Socket(url.getHost(),80);
				}
			}
			return s;
		}
		return null;// Add an error here!
	}
	
	private void setInputStream() throws FileNotFoundException{
		//check	if the file is an image from its extention
		String fileExt = file.getName();
		fileExt=fileExt.substring(fileExt.lastIndexOf(".")+1);
		
		// If file is an image supported by Java (Currently only JPEG, GIF and PNG)
// 		if((fileExt.equalsIgnoreCase("gif")
// 			||fileExt.equalsIgnoreCase("jpg")
// 			||fileExt.equalsIgnoreCase("jpeg")
// 			||fileExt.equalsIgnoreCase("png")) && main.getMaxPixels()>0){
// 			try	{
// 				BufferedImage buf=ImageIO.read(file);
// 				int currentPixels = buf.getWidth()*buf.getHeight();
// 				int maxPixels = main.getMaxPixels();				
// 				if	(currentPixels>maxPixels){
// 					double reduceBy = Math.sqrt(maxPixels)/Math.sqrt(currentPixels);
// 					int	newWidth=(int)Math.round(buf.getWidth()*reduceBy);
// 					int	newHeigth=(int)Math.round(buf.getHeight()*reduceBy);
// 					BufferedImage bufFinal=new BufferedImage(newWidth,newHeigth,BufferedImage.TYPE_INT_RGB);
// 					Graphics2D g=(Graphics2D)bufFinal.getGraphics();
// 					g.setRenderingHint(RenderingHints.KEY_INTERPOLATION,RenderingHints.VALUE_INTERPOLATION_BILINEAR);
// 					g.drawImage(buf,0,0,newWidth,newHeigth,null);
// 					g.dispose();
// 					ByteArrayOutputStream baos=new ByteArrayOutputStream();
// 					if	(fileExt.equalsIgnoreCase("jpg")||fileExt.equalsIgnoreCase("jpeg"))
// 						ImageIO.write(bufFinal,"JPG",baos);
// 					else {// Note, GIF is converted to PNG, we need to change the filename
// 						ImageIO.write(bufFinal,"PNG",baos);
// 						if (fileExt.equalsIgnoreCase("gif")){
// 							// File is a gif, hence, add png to the filename
// 							addPngToFileName = true;
// 						}
// 					}
// 					
// 					// Set the progress to increase by the amount that the image
// 					// is reduced in size
// 					main.setProgress((int)file.length()-baos.size());
// 					fileStream = new ByteArrayInputStream(baos.toByteArray());
// 				}
// 				else{
// 					//if image don't need resize
// 					fileStream = new FileInputStream(file);
// 				}
// 			}
// 			catch (IOException e){
// 				// Error somewhere
// 				fileStream = new FileInputStream(file);
// 			}
// 		}
// 		else{
			//if the file is not an image, or maxPixels is not set
			fileStream = new FileInputStream(file);
// 		}
	}

	private void setBoundary(int length){

		char [] alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
		Random r = new Random();
		String boundaryString ="";
		for (int i=0; i< length; i++)
			boundaryString += alphabet[r.nextInt(alphabet.length)];
		boundary = boundaryString;
	}

	private void setHeaderAndFooter() throws IOException{

		header = new String();
		footer = new String();
		request = new String();

		// AfterContent is what is sent after the Content-Length header field,
		// but before the file itself. The length of this, is what is required
		// by the content-length header (along with the length of the file).
		afterContent = lotsHyphens +"--"+ boundary + lineEnd +
									"Content-Disposition: form-data; name=\"userfile\"; filename=\""+file.getName();
		if (addPngToFileName)
			afterContent += ".png";
		afterContent += "\""+lineEnd+
									"Content-Type: application/octet-stream"+lineEnd+lineEnd;

		//footer = lineEnd + lineEnd + "--"+ lotsHyphens+boundary+"--";
		// LineEnd removed as it was adding an extra byte to the uploaded file
		footer = lineEnd + "--"+ lotsHyphens+boundary+"--" + lineEnd;

		// The request includes the absolute URI to the script which will
		// accept the file upload. This is perfectly valid, although it is
		// normally only used by a client when connecting to a proxy server.
		// COULD CREATE PROBLEMS WITH SOME WEB SERVERS.
		request="POST " + url.toExternalForm() + " HTTP/1.1" + lineEnd;

		// Host that we are sending to (not necesarily connecting to, if behind
		// a proxy)
		header +="Host: " + url.getHost() + lineEnd;

		// Give a user agent just for completeness. This could be changed so that
		// access by the Postlet applet can be logged.
		//header +="User-Agent: Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.7.10)" + lineEnd;
		//Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.7.8)
		header +="User-Agent: Mozilla/5.0 (Java/Postlet; rv:" + main.postletVersion + ")" + lineEnd;


		// Expect a 100-Continue message
		// header +="Expect: 100-continue" + lineEnd;

		// Standard accept
		header +="Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5"+ lineEnd;
		header +="Accept-Language: en-us,en;q=0.5" + lineEnd;
		header +="Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7" + lineEnd;

		// Add the cookie if it is set in the browser
		String cookie = main.getCookie();
		if (cookie.length()>0){
			header +="Cookie: "+cookie+lineEnd;
		}

		header +="Connection: close" + lineEnd;

		// What we are sending.
		header +="Content-Type: multipart/form-data; boundary=" + lotsHyphens + boundary + lineEnd;

		// Length of what we are sending.
		header +="Content-Length: ";
		header += ""+(fileStream.available()+afterContent.length()+footer.length())+lineEnd+lineEnd;
	}
}
