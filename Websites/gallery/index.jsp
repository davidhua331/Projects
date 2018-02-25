<%@ page contentType="text/html;charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.*"%>
<%@ page import="java.io.*" %>
<%@ page import="java.sql.*"%>

<% 
try {
	Class.forName("com.mysql.jdbc.Driver").newInstance();
}
catch(Exception e) {
	out.println("can't load mysql driver");
	out.println(e.toString());
}

String url="jdbc:mysql://127.0.0.1:3306/gallery";
String id="gallery";
String pwd="eecs118";
Connection con = DriverManager.getConnection(url,id,pwd);
Statement stmt;
PreparedStatement pstmt;
ResultSet rs;
String sql;

%>

<% 
 String func1 = request.getParameter("func1");
 String func2 = request.getParameter("func2");
 String func3 = request.getParameter("func3");
 String func4 = request.getParameter("func4");
 String func5 = request.getParameter("func5");
 String func6 = request.getParameter("func6");
 String func7 = request.getParameter("func7");
 String func8 = request.getParameter("func8");
 String func9 = request.getParameter("func9");
 String func10 = request.getParameter("func10");
 String func11 = request.getParameter("func11");
 String func12 = request.getParameter("func12");
 String func13 = request.getParameter("func13");
 String func14 = request.getParameter("func14");
 String func15 = request.getParameter("func15");
 String func16 = request.getParameter("func16");
 String func17 = request.getParameter("func17");
 
 String gname = request.getParameter("gname");
 String gdescr = request.getParameter("gdescr");
 String gallerytype = request.getParameter("gallerytype");
 String aname = request.getParameter("aname");
 String b_y = request.getParameter("birth_year");
 String country = request.getParameter("country");
 String adescr = request.getParameter("adescr");
 String ititle = request.getParameter("ititle");
 String link = request.getParameter("link");
 String gallery_id = request.getParameter("gallery_id");
 String artist_id = request.getParameter("artist_id");
 String detail_id = request.getParameter("detail_id");
 String iyear = request.getParameter("iyear");
 String itype = request.getParameter("itype");
 String iwidth = request.getParameter("iwidth");
 String iheight = request.getParameter("iheight");
 String ilocation = request.getParameter("ilocation");
 String idescr = request.getParameter("idescr");
 String image_id = request.getParameter("image_id");
 String min_year = request.getParameter("min_year");
 String max_year = request.getParameter("max_year");
 String byear = request.getParameter("byear");
 
%>

<html>
  <head>
	<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
	<title> Gallery </title>
  </head>
  <body>
  <b>1. List all the galleries:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="1">
    <input type="submit" value="GO!" name="func1"/>
  </form>
  <% 
  if(func1 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<tr>
		<th style="width: 15%">GalleryID</th>
		<th style="width: 15%">Name</th>
		<th style="width: 15%">Description</th>
	</tr>
  <%stmt = con.createStatement();
	sql="SELECT * FROM gallery.gallery";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("gallery_id")+ "</td>");
		  out.println("<td>"+rs.getString("name")+ "</td>");
		  out.println("<td>"+rs.getString("description")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>2. List all the images and the number of images in a gallery:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="2">
	Gallery: <input name="gallerytype" type="text">
    <input type="submit" value="GO!" name="func2"/>
  </form>
  <% 
  if(func2 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Images in Gallery</caption>
	<tr>
		<th style="width: 15%">ImageID</th>
		<th style="width: 15%">Title</th>
		<th style="width: 15%">Link</th>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">DetailID</th>
		<th style="width: 15%">NumberOfImages</th>
	</tr>
  <%
	Integer GID = 0;
	try{
		GID = Integer.parseInt(gallerytype);
	  }
	catch(NumberFormatException e){
	  out.println("Please input integer: " +e.getMessage());
	  }
    stmt = con.createStatement();
	sql="SELECT *, x.countt FROM gallery.image AS i, (SELECT COUNT(*) as countt FROM gallery.image) AS x WHERE EXISTS (SELECT * FROM gallery.gallery AS g WHERE i.gallery_id=g.gallery_id AND g.gallery_id ="+GID+")";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("image_id")+ "</td>");
		  out.println("<td>"+rs.getString("title")+ "</td>");
		  out.println("<td>"+rs.getString("link")+ "</td>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("detail_id")+ "</td>");
		  out.println("<td>"+rs.getInt("x.countt")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>3. List the details of a given image:</b>
    <form method="post">
    <input name="funcID" type="hidden" value="3">
	ImageID: <input name="image_id" type="text">
    <input type="submit" value="GO!" name="func3"/>
  </form>
  <% 
  if(func3 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Details of Image</caption>
	<tr>
		<th style="width: 15%">ArtistName</th>
		<th style="width: 15%">DetailID</th>
		<th style="width: 15%">Year</th>
		<th style="width: 15%">Type</th>
		<th style="width: 15%">Width</th>
		<th style="width: 15%">Height</th>
		<th style="width: 15%">Location</th>
		<th style="width: 15%">Description</th>
	</tr>
  <%
	Integer ImaID = 0;
	try{
		ImaID = Integer.parseInt(image_id);
	}
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
    }
    stmt = con.createStatement();
	sql="SELECT a.name, d.* FROM gallery.detail AS d JOIN gallery.image AS i ON d.image_id = i.image_id JOIN gallery.artist AS a ON i.artist_id = a.artist_id WHERE i.image_id ="+ImaID;
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getString("a.name")+ "</td>");
		  out.println("<td>"+rs.getInt("d.detail_id")+ "</td>");
		  out.println("<td>"+rs.getInt("d.year")+ "</td>");
		  out.println("<td>"+rs.getString("d.type")+ "</td>");
		  out.println("<td>"+rs.getInt("d.width")+ "</td>");
		  out.println("<td>"+rs.getInt("d.height")+ "</td>");
		  out.println("<td>"+rs.getString("d.location")+ "</td>");
		  out.println("<td>"+rs.getString("d.description")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>4. List the details of an artist:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="4">
	ArtistName: <input name="aname" type="text">
    <input type="submit" value="GO!" name="func4"/>
  </form>
  <% 
  if(func4 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>Details of an Artist by Name</caption>
	<tr>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">Name</th>
		<th style="width: 15%">BirthYear</th>
		<th style="width: 15%">Country</th>
		<th style="width: 15%">Description</th>
	</tr>
  <%
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.artist WHERE name = '"+request.getParameter("aname")+"'";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("name")+ "</td>");
		  out.println("<td>"+rs.getInt("birth_year")+ "</td>");
		  out.println("<td>"+rs.getString("country")+ "</td>");
		  out.println("<td>"+rs.getString("description")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>5. Create a new gallery:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="5">
	Name: <input name="gname" type="text">
	Description: <input name="gdescr" type="text">
	<input type="submit" value="Add" name="func5"/>
  </form>
  <%
  	if(func5 != null){
	sql = "Insert into gallery.gallery(name,description) values(?,?)";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,gname);
	pstmt.setString(2,gdescr);
	pstmt.executeUpdate();
    }
	%>
  <b>6. Create a new artist:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="6">
	Name: <input name="aname" type="text">
	BirthYear:  <input name="birth_year" type="text">
	Country: <input name="country" type="text">
	Description: <input name="adescr" type="text">
	<input type="submit" value="Add" name="func6"/>
  </form>
  <%
   if(func6 != null){
	Integer BY = 0;
	try{
	  BY = Integer.parseInt(b_y);
	}
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
    }
	sql = "Insert into gallery.artist(name,birth_year,country,description) values(?,?,?,?)";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,aname);
	pstmt.setInt(2,BY);
	pstmt.setString(3,country);
	pstmt.setString(4,adescr);
	pstmt.executeUpdate();

    }
	%>
	
  <b>7. Add a new image to a gallery:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="7">
	Title: <input name="ititle" type="text">
	Link: <input name="link" type="text">
	GalleryID: <input name="gallery_id" type="text">
	ArtistID: <input name="artist_id" type="text">
	DetailID: <input name="detail_id" type="text">
	Year:  <input name="iyear" type="text">
	ImageType: <input name="itype" type="text">
	Width: <input name="iwidth" type="text">
	Height: <input name="iheight" type="text">
	Location: <input name="ilocation" type="text">
	Description: <input name="idescr" type="text">
	<input type="submit" value="Add" name="func7"/>
  </form>
  <%
   if(func7 != null){
	Integer GID = 0;
	Integer AID = 0;
	Integer DID = 0;
	Integer iY = 0;
	Integer W = 0;
	Integer H = 0;
	try{
	 GID = Integer.parseInt(gallery_id);
	 AID = Integer.parseInt(artist_id);
	 DID = Integer.parseInt(detail_id);
	 iY = Integer.parseInt(iyear);
	 W = Integer.parseInt(iwidth);
	 H = Integer.parseInt(iheight);
	}
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
    }
	sql = "Insert into gallery.image(title,link,gallery_id,artist_id,detail_id) values(?,?,?,?,?)";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,ititle);
	pstmt.setString(2,link);
	pstmt.setInt(3,GID);
	pstmt.setInt(4,AID);
	pstmt.setInt(5,DID);
	pstmt.executeUpdate();
	
	sql = "Insert into gallery.detail(image_id,year,type,width,height,location,description) values(?,?,?,?,?,?,?)";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setInt(1,DID);
	pstmt.setInt(2,iY);
	pstmt.setString(3,itype);
	pstmt.setInt(4,W);
	pstmt.setInt(5,H);
	pstmt.setString(6,ilocation);
	pstmt.setString(7,idescr);
	pstmt.executeUpdate();
    
	
	}
	%>
 
  <b>8. Delete an image from the gallery:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="8">
	ImageID: <input name="image_id" type="text">
	<input type="submit" value="Delete" name="func8"/>
  </form>
  <%
  if(func8 != null){
	Integer ImID = 0;
	try{
	  ImID = Integer.parseInt(image_id);
	}
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
    }
	sql = "DELETE FROM gallery.detail WHERE image_id = ?";
    pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
    pstmt.setInt(1,ImID);
    pstmt.executeUpdate();

    sql = "DELETE FROM gallery.image WHERE image_id = ?";
    pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
    pstmt.setInt(1,ImID);
    pstmt.executeUpdate();
  }  
	%>
	
  <b> 9. Modify the details of an image:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="9">
	ImageID: <input name="image_id" type="text">
	Title: <input name="ititle" type="text">
	Link: <input name="link" type="text">
	Year:  <input name="iyear" type="text">
	ImageType: <input name="itype" type="text">
	Width: <input name="iwidth" type="text">
	Height: <input name="iheight" type="text">
	Location: <input name="ilocation" type="text">
	Description: <input name="idescr" type="text">
	<input type="submit" value="Modify" name="func9"/>
  </form>
  <%
   if(func9 != null){
	Integer ImageID = 0;
	Integer iYear = 0;
	Integer Width = 0;
	Integer Height = 0;
	try{
	  ImageID = Integer.parseInt(image_id);
	  iYear = Integer.parseInt(iyear);
	  Width = Integer.parseInt(iwidth);
	  Height = Integer.parseInt(iheight);
	}
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
    }
	
	sql = "UPDATE gallery.image SET title = ?, link = ? WHERE image_id = ?";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,ititle);
	pstmt.setString(2,link);
	pstmt.setInt(3,ImageID);
	pstmt.executeUpdate();
	
	sql = "UPDATE gallery.detail SET year = ?, type = ?, width = ?, height = ?, location = ?, description = ? WHERE image_id = ?";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setInt(1,iYear);
	pstmt.setString(2,itype);
	pstmt.setInt(3,Width);
	pstmt.setInt(4,Height);
	pstmt.setString(5,ilocation);
	pstmt.setString(6,idescr);
	pstmt.setInt(7,ImageID);
	pstmt.executeUpdate();
    }
	%>
  <b>10.Modify the details of an artist:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="10">
	ArtistID: <input name="artist_id" type="text">
	Name: <input name="aname" type="text">
	BirthYear: <input name="birth_year" type="text">
	Country: <input name="country" type="text">
	Description: <input name="adescr" type="text">
	<input type="submit" value="Modify" name="func10"/>
  </form>
  <%
   if(func10 != null){
	Integer ArtID = 0;
	Integer aYear = 0;
	try{
	  ArtID = Integer.parseInt(artist_id);
	  aYear = Integer.parseInt(b_y);
	  }
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
	  }
	sql = "UPDATE gallery.artist SET name = ?, birth_year = ?, country = ?, description = ? WHERE artist_id = ?";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,aname);
	pstmt.setInt(2,aYear);
	pstmt.setString(3,country);
	pstmt.setString(4,adescr);
	pstmt.setInt(5,ArtID);
	pstmt.executeUpdate();
    }
	%>
  <b>11.Modify the title and description of a gallery:</b>
  <form method="post">
	<input name="funcID" type="hidden" value="11">
	GalleryID: <input name="gallery_id" type="text">
	Name: <input name="gname" type="text">
	Description: <input name="gdescr" type="text">
	<input type="submit" value="Modify" name="func11"/>
  </form>
  <%
   if(func11 != null){
	Integer GalID = 0;
	try{
	  GalID = Integer.parseInt(gallery_id);
	  }
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
	  }
	
	sql = "UPDATE gallery.gallery SET name = ?, description = ? WHERE gallery_id = ?";
	pstmt = con.prepareStatement(sql, PreparedStatement.RETURN_GENERATED_KEYS);
	pstmt.setString(1,gname);
	pstmt.setString(2,gdescr);
	pstmt.setInt(3,GalID);
	pstmt.executeUpdate();
    }
	%>
  <b>12.Find the images by type:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="12">
	Images(type): <input name="itype" type="text">
    <input type="submit" value="GO!" name="func12"/>
  </form>
  <% 
  if(func12 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Images by Type</caption>
	<tr>
		<th style="width: 15%">ImageID</th>
		<th style="width: 15%">Title</th>
		<th style="width: 15%">Link</th>
		<th style="width: 15%">GalleryID</th>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">DetailID</th>
	</tr>
  <%
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.image AS i WHERE EXISTS (SELECT * FROM gallery.detail AS d WHERE i.image_id = d.image_id AND d.type = '"+request.getParameter("itype")+"')";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("image_id")+ "</td>");
		  out.println("<td>"+rs.getString("title")+ "</td>");
		  out.println("<td>"+rs.getString("link")+ "</td>");
		  out.println("<td>"+rs.getInt("gallery_id")+ "</td>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("detail_id")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>

  <b>13.Find the images by a given range of creation year:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="13">
	MinYear: <input name="min_year" type="text">
	MaxYear: <input name="max_year" type="text">
    <input type="submit" value="GO!" name="func13"/>
  </form>
  <% 
  if(func13 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Images by Range of Creation Year</caption>
	<tr>
		<th style="width: 15%">ImageID</th>
		<th style="width: 15%">Title</th>
		<th style="width: 15%">Link</th>
		<th style="width: 15%">GalleryID</th>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">DetailID</th>
	</tr>
  <%
	Integer Min = 0;
	Integer Max = 0;
	try{
      Min = Integer.parseInt(min_year);
	  Max = Integer.parseInt(max_year);
	  }
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
	  }

	stmt = con.createStatement();
	sql="SELECT * FROM gallery.image AS i WHERE EXISTS (SELECT * FROM gallery.detail AS d WHERE i.image_id = d.image_id AND d.year > "+Min+" AND d.year < "+Max+")";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("image_id")+ "</td>");
		  out.println("<td>"+rs.getString("title")+ "</td>");
		  out.println("<td>"+rs.getString("link")+ "</td>");
		  out.println("<td>"+rs.getInt("gallery_id")+ "</td>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("detail_id")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>14.Find the images by artist name:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="14">
	Images(Artist Name): <input name="aname" type="text">
    <input type="submit" value="GO!" name="func14"/>
  </form>
  <% 
  if(func14 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Images by Artist</caption>
	<tr>
		<th style="width: 15%">ImageID</th>
		<th style="width: 15%">Title</th>
		<th style="width: 15%">Link</th>
		<th style="width: 15%">GalleryID</th>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">DetailID</th>
	</tr>
  <%
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.image AS i WHERE EXISTS (SELECT * FROM gallery.artist AS a WHERE i.artist_id = a.artist_id AND a.name = '"+request.getParameter("aname")+"')";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("image_id")+ "</td>");
		  out.println("<td>"+rs.getString("title")+ "</td>");
		  out.println("<td>"+rs.getString("link")+ "</td>");
		  out.println("<td>"+rs.getInt("gallery_id")+ "</td>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("detail_id")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>15.Find the images by location:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="15">
	Images(location): <input name="ilocation" type="text">
    <input type="submit" value="GO!" name="func15"/>
  </form>
  <% 
  if(func15 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Images by Location</caption>
	<tr>
		<th style="width: 15%">ImageID</th>
		<th style="width: 15%">Title</th>
		<th style="width: 15%">Link</th>
		<th style="width: 15%">GalleryID</th>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">DetailID</th>
	</tr>
  <%
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.image AS i WHERE EXISTS (SELECT * FROM gallery.detail AS d WHERE i.image_id = d.image_id AND d.location = '"+request.getParameter("ilocation")+"')";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("image_id")+ "</td>");
		  out.println("<td>"+rs.getString("title")+ "</td>");
		  out.println("<td>"+rs.getString("link")+ "</td>");
		  out.println("<td>"+rs.getInt("gallery_id")+ "</td>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("detail_id")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>16.Find the Artists by Country:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="16">
	Country: <input name="country" type="text">
    <input type="submit" value="GO!" name="func16"/>
  </form>
  <% 
  if(func16 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Artists by Country</caption>
	<tr>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">Name</th>
		<th style="width: 15%">BirthYear</th>
		<th style="width: 15%">Country</th>
		<th style="width: 15%">Description</th>
	</tr>
  <%
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.artist WHERE country = '"+request.getParameter("country")+"'";
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("name")+ "</td>");
		  out.println("<td>"+rs.getInt("birth_year")+ "</td>");
		  out.println("<td>"+rs.getString("country")+ "</td>");
		  out.println("<td>"+rs.getString("description")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  <b>17.Find the artists by birth year:</b>
  <form method="post">
    <input name="funcID" type="hidden" value="17">
	BirthYear: <input name="byear" type="text">
    <input type="submit" value="GO!" name="func17"/>
  </form>
  <% 
  if(func17 != null){
  %>
  <table border="1" cellpadding="5" style = "width: 70%">
	<caption>List of Artists by Country</caption>
	<tr>
		<th style="width: 15%">ArtistID</th>
		<th style="width: 15%">Name</th>
		<th style="width: 15%">BirthYear</th>
		<th style="width: 15%">Country</th>
		<th style="width: 15%">Description</th>
	</tr>
  <%
	Integer Byear = 0;
	try{
	  Byear = Integer.parseInt(byear);
	  }
	catch(NumberFormatException e){
	  out.print("Please input integer: " +e.getMessage());
	  }
    stmt = con.createStatement();
	sql="SELECT * FROM gallery.artist WHERE birth_year ="+Byear;
	rs=stmt.executeQuery(sql);
	while (rs.next()) {
		out.println("<tr>");
		  out.println("<td>"+rs.getInt("artist_id")+ "</td>");
		  out.println("<td>"+rs.getString("name")+ "</td>");
		  out.println("<td>"+rs.getInt("birth_year")+ "</td>");
		  out.println("<td>"+rs.getString("country")+ "</td>");
		  out.println("<td>"+rs.getString("description")+ "</td>");
		out.println("</tr>");
	}
  %>
  </table>
  <%}%>
  
  </body>

</html>