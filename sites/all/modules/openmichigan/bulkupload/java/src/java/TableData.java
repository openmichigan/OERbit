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

import java.io.*;
import java.util.Vector;
import javax.swing.*;
import javax.swing.table.*;

public class TableData extends AbstractTableModel
{
	Vector myTable;
	int colCount;
	String [] headers = {"Filename","Size - Kb"};
	int totalFileSize;

	public TableData(String file, String size){

		myTable = new Vector();
		colCount = 2;
		totalFileSize =0;
		headers[0] = file;
		headers[1] = size;
	}

	public String getColumnName(int i){
		if(i==1 && totalFileSize !=0)
		{
			double totalFileSizeMB = totalFileSize/ 10485.76;
			totalFileSizeMB = (double)Math.round(totalFileSizeMB)/100;
			return headers[i]+" ("+totalFileSizeMB+"Mb)";
		}
		else
			return headers[i];
	}

	public int getColumnCount(){
		return colCount;
	}

	public int getRowCount()
		{
			return myTable.size();}

		public int getTotalFileSize()
		{
			return totalFileSize;}

	public Object getValueAt(int row, int col)
		{
			return ((Object[])myTable.elementAt(row))[col];}


	public void formatTable(String [][] data, int dataLength)
	{
			totalFileSize =0;
			myTable = new Vector();
			int j=0;
			while (j<dataLength)
			{
				Object[] row = new Object[colCount];
				for (int k=0; k < colCount; k++)
				{
					if(k==1)
					{
						try{
							int thisFileSize = Integer.parseInt(data[j][k]);
							totalFileSize += thisFileSize;
							thisFileSize /=102.4;
							double thisFileKb = (double)thisFileSize/10;
							row[k] = new Double(thisFileKb);}
						catch(NumberFormatException nfe){;}
					}
					else
						row[k] = data[j][k];
				}
				myTable.addElement(row);
				j++;
			}
			fireTableChanged(null);
		}
}



