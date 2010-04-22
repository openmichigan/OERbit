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

