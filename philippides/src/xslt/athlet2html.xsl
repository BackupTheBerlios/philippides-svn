<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
<xsl:strip-space elements="*"/>

<xsl:template match="athlet">
<html>
<head>
  <title>Athlet data</title>
  <meta name="GENERATOR" content="Philippides"/>

<style type="text/css">
<![CDATA[
body{
	background-color:#3024b0;
	background-image: url(]]><xsl:value-of select="imagepath"/>/runner.png<![CDATA[);
	background-repeat: no-repeat;
	background-position: 0 35pt;
	background-attachment: fixed;
	position: relative;
	margin: 0;
	padding: 0;
}

div#content{
	background-color:#8C92FF;
	background-image:url(]]><xsl:value-of select="imagepath"/>/runner-light.png<![CDATA[);
	background-repeat:no-repeat;
	background-position: 0 35pt;
	background-attachment:fixed;
	position:absolute;
	padding: 10px;
	top:10pt;
	right:10pt;
<!--	bottom: 10pt;-->
	height: 200pt;
	left:70pt;
	border:thick solid black;
	font: 13px Verdana, sans-serif;
}

div#table{
	background-color:#D8DCFF;
	position:absolute;
	padding: 10px;
	top:40pt;
	right:10pt;
	bottom:10pt;
	left:120pt;
	border:thin solid black;
}

h1 {
	margin: -9px -9px 0.5em;
	padding: 10px 0 5px;
	text-align: center;
	background: #476796;
	color: #8C92FF;
	letter-spacing: 0.5em;
	font: bold 15px sans-serif;
	height: 20px;
	vertical-align: top;
	white-space: nowrap;
	border: thin solid black;
	}
	
td#b { font-weight: bold;} 
td { font-size: 10px;}
]]>
</style>
</head>

<body>
<div id="content">
<h1>Athlet data</h1>
<div align="center" id="table">
<table border="0">
  <col/>
  <col/>
  <col/>
  <col/>
  <tbody>
    <tr>
      <td id="b">  First name </td>
      <td> <xsl:value-of select="firstname"/> </td>
	<td width="30"></td>      
      <td id="b"> Last name </td>
      <td> <xsl:value-of select="lastname"/> </td>
    </tr>
    <tr>
      <td id="b"> Gender </td>
      <td> <xsl:apply-templates select="gender"/> </td>
      <td width="30"></td>
      <td id="b"> Birthday </td>
      <td> <xsl:value-of select="birthday"/> </td>
    </tr>
    <tr>
      <td id="b"> Weight </td>
      <td> <xsl:value-of select="weight"/> </td>
      <td width="30"></td>
      <td id="b"> Height </td>
      <td> <xsl:value-of select="height"/> </td>
    </tr>
    <tr>
      <td id="b"> Running frequency </td>
      <td> <xsl:value-of select="runningfreq"/> </td>
      <td width="30"></td>
      <td id="b"> Average distance </td>
      <td> <xsl:value-of select="avgpulse"/> </td>
    </tr>
    <tr>
      <td id="b"> 5 km time </td>
      <td> <xsl:value-of select="kmtime5"/> </td>
      <td width="30"></td>
      <td id="b"> 10 km time </td>
      <td> <xsl:value-of select="kmtime10"/> </td>
    </tr>
    <tr>
      <td id="b"> Biggest distance </td>
      <td> <xsl:value-of select="biggestdist"/> </td>
      <td width="30"></td>
      <td id="b"> Average pulse </td>
      <td> <xsl:value-of select="avgpulse"/> </td>
    </tr>
    <tr>
      <td id="b"> Morning pulse </td>
      <td> <xsl:value-of select="morningpulse"/> </td>
      <td width="30"></td>
      <td>  </td>
      <td>  </td>
    </tr>
  </tbody>
</table>
</div>
</div>
</body>
</html>
</xsl:template>

<xsl:template match="gender">
    <xsl:value-of select="@value"/>
</xsl:template>

</xsl:stylesheet>
