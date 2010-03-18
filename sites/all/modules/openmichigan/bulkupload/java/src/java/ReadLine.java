/*	Copyright (C) 2006 Simon David Rycroft

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

import java.io.BufferedReader;
import java.io.IOException;

public class ReadLine extends Thread {

	BufferedReader input;
	String read;
	private static final String newLine = "\n";
	UploadThread parent;

	public ReadLine (BufferedReader i, UploadThread p){

		parent = p;
		input = i;
		read = "";
	}

	public synchronized void run(){

		try {
			String line="";
			while ((line = input.readLine())!=null){
				this.read += line + newLine;
				if (line.equals("")){
					try {
						parent.notify();
					}
					catch (IllegalMonitorStateException ime){
						// It appears the thread didn't need notifying
						// so, lets not worry about it (Timed out).
					}
				}
			}
		}
		catch (IOException ioe){
			// Likely as a result of the socket being closed.
			// Notify parent (may be waiting).
			try {
				parent.notify();
			}
			catch (IllegalMonitorStateException ime){
				// It appears the thread didn't need notifying
				// so, lets not worry about it (Timed out).
			}
		}
	}

	public String getRead(){

		return this.read;
	}
}
