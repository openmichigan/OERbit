/*
 * COPYRIGHT 2011
 *
 * The Regents of the University of Michigan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * any later version.
 *
 * You may not use the name of The University of Michigan in any
 * advertising or publicity pertaining to the use of distribution of this software
 * without specific, written prior authorization. If the above copyright notice
 * or any other identification of the University of Michigan is included in any
 * copy of any portion of this software, then the disclaimer below must
 * also be included.
 *
 * THIS SOFTWARE IS PROVIDED AS IS, WITHOUT REPRESENTATION
 * FROM THE UNIVERSITY OF MICHIGAN AS TO ITS FITNESS FOR ANY
 * PURPOSE, AND WITHOUT WARRANTY BY THE UNIVERSITY OF
 * MICHIGAN OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING
 * WITHOUT LIMITATION THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE
 * REGENTS OF THE UNIVERSITY OF MICHIGAN SHALL NOT BE LIABLE
 * FOR ANY DAMAGES, INCLUDING SPECIAL, INDIRECT, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, WITH RESPECT TO ANY CLAIM ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OF THE SOFTWARE, EVEN
 * IF IT HAS BEEN OR IS HEREAFTER ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGES.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

var gIntervalId = null;

function progressCheck()
{
	$.ajax({
  		url: 'zip_download/progress',
  		type: 'GET',
  		aync: true,
  		dataType: 'json',
  		success: function (data) 
  		{
			if (typeof (data.percent) === 'undefined' && gIntervalId !== null)
			{
				clearInterval (gIntervalId);
				gIntervalId = null;
			}
  			
			if (data.percent >= 100)
			{
				clearInterval (gIntervalId);
				gIntervalId = null;
				$(".ui-progressbar-value").css ("background-image", "none");
				$("#progressbar").progressbar ('option', 'value', 100);
			}
			else
			{
				$("#progressbar").progressbar ('option', 'value', data.percent);
			}
  		}
	});
}

$(document).ready(function() {
	$("#edit-download").click(
		function (event) 
		{
			$("#progressbar").progressbar ({ value: 0 });
		    gIntervalId = setInterval( "progressCheck()", 2500 );
			$("#edit-download").attr('disabled', 'disabled');
		    $("#zip-download-form").submit();
		    return true;
		}
	);
});

