<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
<xsl:strip-space elements="*"/>

<xsl:template match="run">
<html>
<head>
  <title>Athlet data</title>
  <meta name="GENERATOR" content="Philippides"/>

<style type="text/css">
<![CDATA[
body{
	background-color:#3024b0;
	background-repeat: no-repeat;
	background-position: 0 35pt;
	background-attachment: fixed;
	position: relative;
	margin: 0;
	padding: 0;
}

div#content{
	background-color:#8C92FF;
	background-repeat:no-repeat;
	background-position: 0 35pt;
	background-attachment:fixed;
	position:absolute;
	padding: 10px;
	top:10pt;
	right:10pt;
<!--	bottom: 10pt;-->
	height: 130pt;
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
	
td#b {font-weight: bold;}
td { font-size: 10px;}
]]>
</style>
</head>

<body>
<div id="content">
<h1>Run data</h1>
<div align="center" id="table">
<table border="0">
  <col/>
  <col/>
  <col/>
  <col/>
  <tbody>
    <tr>
      <td id="b"> Date </td>
      <td> <xsl:value-of select="date"/> </td>
	<td width="30"></td>      
      <td id="b"> Time </td>
      <td> <xsl:value-of select="time"/> </td>
    </tr>
    <tr>
      <td id="b"> Pulse </td>
      <td> <xsl:value-of select="pulse"/> </td>
      <td width="30"></td>
      <td id="b"> Weather </td>
      <td> <xsl:apply-templates select="weather"/> </td>
    </tr>
    <tr>
      <td id="b"> Impression </td>
      <td> <xsl:apply-templates select="impression"/> </td>
      <td width="30"></td>
      <td> </td>
      <td> </td>
    </tr>
    <tr>
      <td id="b"> Comment </td>
      <td colspan="4"> <xsl:value-of select="comment"/> </td>
    </tr>
 </tbody>
</table>
</div>
</div>
</body>
</html>
</xsl:template>

<xsl:template match="weather">
    <xsl:value-of select="@value"/>
</xsl:template>

<xsl:template match="impression">
    <xsl:value-of select="@value"/>
</xsl:template>

</xsl:stylesheet>
