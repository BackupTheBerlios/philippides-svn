<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" indent="yes"/>
<xsl:strip-space elements="*"/>


<!-- the main html framework -->
<xsl:template match="/">
    <html>
    <head>
	<title>Philippides run database</title>
	<style>
	    h1{ font: bold 28px sans-serif; color: blue}
	    h2{ font: bold 14px sans-serif; color: blue; text-align:left}
	    p { font: 12px sans-serif}
	</style>
    </head>

    <body>
	<h1>Philippides run database</h1>
	<xsl:apply-templates/>
    </body>
    </html>
</xsl:template>

<!-- a run entity -->    
<xsl:template match="rundb">
    <xsl:for-each select="run">
	<p>
	<hr/>
	<h2>
	    Lauf No: <xsl:value-of select="position()"/> vom <xsl:value-of select="date"/>
	</h2>
	    Time:	<xsl:value-of select="time"/><br/>
	    Length:	<xsl:value-of select="length"/><br/>
	    Pulse:	<xsl:value-of select="pulse"/><br/>
	    Comment:	<xsl:value-of select="comment"/><br/>	    
	    <xsl:apply-templates select="weather"/>
	    <xsl:apply-templates select="impression"/>
	</p> 
    </xsl:for-each>
</xsl:template>

<!-- the weather choice -->
<xsl:template match="weather">
    Weather: <xsl:value-of select="@value"/><br/>
</xsl:template>

<!-- the impression choice -->
<xsl:template match="impression">
    Impression: <xsl:value-of select="@value"/><br/>
</xsl:template>

</xsl:stylesheet>
