<?php
	/**
	*  @file This is an example form which allows users to enter HTML or a URL
	*		 and then checks thecontent against several reporters and guidelines.
	*
	*/
	if(!$_POST){ 
	?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
	<html>
		<head>
			<title>Quail Doc</title>
		</head>
		<body>
		<div style="background: #d1eaf1"><pre>
	</pre></div>
	<div>
	<form action="test_form.php" method="post">
	<p><label for="url">URL:</label> <input type="text" id="url" name="url"></p>
	<p><label for="html">HTML:</label> <textarea name="html"></textarea></p>
	<p><label for="reporter">Reporter:</label>
		<select id="reporter" name="reporter">
			<option value="static">Static Reporter</option>
			<option value="demo">Demonstration Reporter</option>
			<option value="xml">XML</option>
			<option value="array">Array</option>
		</select>
	</p>
	<p><label for="guideline">Guideline:</label>
		<select id="guideline" name="guideline">
			<option value="all">All Tests</option>
			<option value="wcag1a">WCAG 1.0 A</option>
			<option value="wcag1aa">WCAG 1.0 AA</option>
			<option value="wcag1aaa">WCAG 1.0 AAA</option>
			<option value="wcag2a">WCAG 2.0 A</option>
			<option value="wcag2aa">WCAG 2.0 AA</option>
			<option value="wcag2aaa">WCAG 2.0 AAA</option>
			<option value="section508">Section 508</option>
		</select>
	</p>
	<p><input type="submit" value="Go"></p>
	</form>
	</div>
		</body>
	</html>
<?php } 
else { 	require_once('../quail/quail.php');

	      
		        if($_POST['url'])
		        	$quail = new quail($_POST['url'], $_POST['guideline'], 'uri', $_POST['reporter']);
		        if($_POST['html'])
		        	$quail = new quail($_POST['html'], $_POST['guideline'], 'string', $_POST['reporter']);

				
				$quail->runCheck();
				if($_POST['reporter'] != 'array')
					print $quail->getReport(array('display_level' => QUAIL_TEST_SEVERE));
				else
					var_dump($quail->getReport(array('display_level' => QUAIL_TEST_SEVERE)));
			}  ?>
