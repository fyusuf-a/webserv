<!DOCTYPE html>
<html>
    <head>
        <title>Webserv</title>
		<link rel="stylesheet" href="https://cdn.simplecss.org/simple.min.css">
    </head>
    <body>
    <header>
    <nav>
		  <a href="/">Home</a>
		  <a href="/php/php-ini.php" >PHP cgi</a>
		  <a href="/php/cookie.php" >Cookie page</a>
		  <a href="https://www.youtube.com/watch?v=YxjY_YTksKM" >Medieval exclusive song</a>
	</nav>
      <h1>Webserv</h1>
      <p>A simple Nginx clone</p>
    </header>

	<p>Setting  the following cookies</p>
	<ul>
		<li>webserv=42project</li>
		<li>outstanding_project=true</li>
		<li>bonus=good</li>
	</ul>
	<?php	setcookie('webserv', '42project');
			setcookie('outstanding_project', 'true');
			setcookie('bonus', 'good');
	?>
    </body>
</html>

