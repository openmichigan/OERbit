/*
 * $Id: JavascriptListener.java 165 2008-06-09 22:26:24Z sdrycroft $
 */

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

public class JavascriptListener extends Thread{

	Main main;

	public JavascriptListener(Main m) {
		main = m;
	}

	public void run() {

		 while (true){
			 if (main.getJavascriptStatus()){
				 main.setJavascriptStatus();
				 if (main.getButtonClicked() == 0){
					 main.addClick();
				 }
				 else if (main.getButtonClicked() == 1){
					 if (main.isUploadEnabled())
					 main.uploadClick();
				 }
				 else if (main.getButtonClicked() == 2){
					 main.cancelUpload();
				 }
				 else if (main.getButtonClicked() == 3){
					 main.removeFile(main.getFileToRemove());
				 }
			 }
			 try{
				 sleep(100);// Interval between checking for an event.
				 // This should be set as low as possible, without slowing down the
				 // web browser/applet.
			 }
			 catch (Throwable t){
				; // Ignore sleep interuption (Likely due to a page refresh.
			 }
		 }
	}
}
