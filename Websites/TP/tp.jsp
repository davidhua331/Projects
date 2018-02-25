<%@ page contentType="text/html;charset=UTF-8" pageEncoding="UTF-8" %>
<%@ page import="java.util.*"%>
<%@ page import="java.io.*" %>

<% 
 String func1 = request.getParameter("func1");
 
 String sAB_CD = request.getParameter("AB_CD");
 String sAC_BD = request.getParameter("AC_BD");
 String sEF = request.getParameter("EF");
 String sEG = request.getParameter("EG");
 String sFG = request.getParameter("FG");
 String sAngE = request.getParameter("angleE");
 String sAngF = request.getParameter("angleF");
 String sAngG = request.getParameter("angleG");
 Double dAB_CD;
 Double dAC_BD;
 Double dAE = 0.0;
 Double dAF = 0.0;
 Double dBF = 0.0;
 Double dBD = 0.0;
 Double dCG = 0.0;
 Double dDG = 0.0;
 Double dCE = 0.0;
 Double dEF;
 Double dEG;
 Double dFG;
 Double dAngE;
 Double dAngF;
 Double dAngG;

 Boolean NoSolution;
 NoSolution = false;
%>

<html>
  <head>
	<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
	<title> Geometry Problem Solver </title>
  </head>
  <body>
  
    <p> Folding Rectangle Problem </p>
    <img src="images/geometry.jpg" align="left" />
  
    <div>

    <b>Input: Please include Length,Width,2 Sides of Triangle, and an Angle, With Assumption E is on Line AC, F is on line AB, and G is on line CD </b>
    <form method="post" action="">
	  <input name="funcID" type="hidden" value="9">
	  <label>Length AB/CD: </label> <input name="AB_CD" type="number" step="any" placeholder = "?"> <br>
	  <label>Width AC/BD: </label> <input name="AC_BD" type="number" step="any" placeholder = "?"> <br>
	  <label>Line EF: </label> <input name="EF" type="number" placeholder = "?"> <br>
	  <label>Line EG: </label> <input name="EG" type="number" placeholder = "?"> <br>
	  <label>Line FG: </label> <input name="FG" type="number" placeholder = "?"> <br>
	  <label>Angle e: </label> <input name="angleE" type="number" placeholder = "?"> <br>
	  <label>Angle f: </label> <input name="angleF" type="number" placeholder = "?"> <br>
	  <label>Angle g: </label> <input name="angleG" type="number" placeholder = "?"> <br>
	  <input type="submit" value="Calculate" name="func1"/>
    </form>
  <%
   if(func1 != null){
	 dAB_CD = TryToParse(sAB_CD);
	 dAC_BD = TryToParse(sAC_BD);
	 dEF = TryToParse(sEF);
	 dEG = TryToParse(sEG);
	 dFG = TryToParse(sFG);
	 dAngE = TryToParse(sAngE);
	 dAngF = TryToParse(sAngF);
	 dAngG = TryToParse(sAngG);
	 
	 if(dAB_CD>0.0 && dAC_BD>0.0 && dEF>0.0 && dEG>0.0 && (dAngE>0.0 || dAngF>0.0 || dAngG>0.0)){
		if(dAngE>0.0 && dAngE<180.0){
			Double fg_sqr = (dEF*dEF)+(dEG*dEG)-(2*dEF*dEG*Math.cos(Math.toRadians(dAngE))); /* find missing side */
			dFG = Math.sqrt(fg_sqr);
			
			dAngG = Math.toDegrees(Math.asin((dEF*Math.sin(Math.toRadians(dAngE)))/dFG));  /* find AngG */
			
			dAngF = 180.0 - dAngE - dAngG; /* find AngF */
			
		}
		else if(dAngF>0.0 && dAngF<180.0){
			dAngG = Math.toDegrees(Math.asin((dEF*Math.sin(Math.toRadians(dAngF)))/dEG));
			
			dAngE = 180.0 - dAngF - dAngG;
			
			Double fg_sqr = (dEF*dEF)+(dEG*dEG)-(2*dEF*dEG*Math.cos(Math.toRadians(dAngE))); /* find missing side */
			dFG = Math.sqrt(fg_sqr);
			
		}
		else if(dAngG>0.0 && dAngG<180.0){
			dAngF = Math.toDegrees(Math.asin((dEG*Math.sin(Math.toRadians(dAngG)))/dEF));
			
			dAngE = 180.0 - dAngF - dAngG;
			
			Double fg_sqr = (dEF*dEF)+(dEG*dEG)-(2*dEF*dEG*Math.cos(Math.toRadians(dAngE))); /* find missing side */
			dFG = Math.sqrt(fg_sqr);
			
		}
		else{
			out.println("Input Angle out of limit");
			NoSolution = true;
		}
		
		if((dEF + dFG + dEG) > (Math.sqrt(dAB_CD*dAB_CD + dAC_BD*dAC_BD) +  dAC_BD + dAB_CD)){
			out.println("length of sides of triangle are too long");
			NoSolution = true;
		}
		else if((dEF + dFG + dEG) < 2*dAB_CD){
			out.println("triangle is too small");
			NoSolution = true;
		}
		else if(dFG < dAC_BD){
			out.println("triangle is too small");
			NoSolution = true;
		}
	}
	 else if(dAB_CD>0.0 && dAC_BD>0.0 && dEG>0.0 && dFG>0.0 && (dAngE>0.0 || dAngF>0.0 || dAngG>0.0)){
		if(dAngE>0.0 && dAngE<180.0){
			dAngF = Math.toDegrees(Math.asin((dEG*Math.sin(Math.toRadians(dAngE)))/dFG));
			
			dAngG = 180.0 - dAngE - dAngF;
			
			Double ef_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEF = Math.sqrt(ef_sqr);
		}
		else if(dAngF>0.0 && dAngF<180.0){
			dAngE = Math.toDegrees(Math.asin((dFG*Math.sin(Math.toRadians(dAngF)))/dEG));
			
			dAngG = 180.0 - dAngE - dAngF;
			
			Double ef_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEF = Math.sqrt(ef_sqr);
		}
		else if(dAngG>0.0 && dAngG<180.0){
			Double ef_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEF = Math.sqrt(ef_sqr);
			
			dAngF = Math.toDegrees(Math.asin((dEG*Math.sin(Math.toRadians(dAngG)))/dEF));
			
			dAngE = 180.0 - dAngF - dAngG;
		}
		else{
			out.println("Input Angle out of limit");
			NoSolution = true;
		}
		
		if((dEF + dFG + dEG) > (Math.sqrt(dAB_CD*dAB_CD + dAC_BD*dAC_BD) +  dAC_BD + dAB_CD)){
			out.println("length of sides of triangle are too long");
			NoSolution = true;
		}
		else if((dEF + dFG + dEG) < 2*dAB_CD){
			out.println("triangle is too small");
			NoSolution = true;
		}
		else if(dFG < dAC_BD){
			out.println("triangle is too small");
			NoSolution = true;
		}
	 }
	 else if(dAB_CD>0.0 && dAC_BD>0.0 && dEF>0.0 && dFG>0.0 && (dAngE>0.0 || dAngF>0.0 || dAngG>0.0)){
		if(dAngE>0.0 && dAngE<180.0){
			dAngG = Math.toDegrees(Math.asin((dEF*Math.sin(Math.toRadians(dAngE)))/dFG));;
			
			dAngF = 180.0 - dAngE - dAngG;
			
			Double eg_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEG = Math.sqrt(eg_sqr);
		}
		else if(dAngF>0.0 && dAngF<180.0){
			Double eg_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEG = Math.sqrt(eg_sqr);
			
			dAngE = Math.toDegrees(Math.asin((dFG*Math.sin(Math.toRadians(dAngF)))/dEG));
			
			dAngG = 180.0 - dAngE - dAngF;
			
		}
		else if(dAngG>0.0 && dAngG<180.0){
			dAngE = Math.toDegrees(Math.asin((dFG*Math.sin(Math.toRadians(dAngG)))/dEF));
		
			dAngF = 180.0 - dAngE - dAngG;
			
			Double eg_sqr = (dFG*dFG)+(dEG*dEG)-(2*dFG*dFG*Math.cos(Math.toRadians(dAngG))); 
			dEG = Math.sqrt(eg_sqr);
			
		}
		else{
			out.println("Input Angle out of limit");
			NoSolution = true;
		}
		
		if((dEF + dFG + dEG) > (Math.sqrt(dAB_CD*dAB_CD + dAC_BD*dAC_BD) +  dAC_BD + dAB_CD)){
			out.println("length of sides of triangle are too long");
			NoSolution = true;
		}
		else if((dEF + dFG + dEG) < 2*dAB_CD){
			out.println("triangle is too small");
			NoSolution = true;
		}
		else if(dFG < dAC_BD){
			out.println("triangle is too small");
			NoSolution = true;
		}
	 }
	 else{
		out.println("Not Enough Information");
		NoSolution = true;
	 }
	 
	%>

  </div>
  <div>
    <b>Output:</b>
	<%if(NoSolution){
	  %>
	  No Solution
	<%}
	  else{
	  %>
    <table border="1" cellpadding="5" style = "width: 30%">
	  <tr>
		<th style="width: 50%">Variable</th>
		<th style="width: 50%">Value</th>
	  </tr>
	  <tr>
	    <td>Line AB: </td> <td> <%out.println(dAB_CD);%> </td> <tr>
	    <td>Line CD: </td> <td> <%out.println(dAB_CD);%> </td> <tr>
	    <td>Line AC: </td> <td> <%out.println(dAC_BD);%> </td> <tr>
	    <td>Line BD: </td> <td> <%out.println(dAC_BD);%> </td> <tr>
	    <td>Line EF: </td> <td> <%out.println(dEF);%> </td> <tr>
	    <td>Line EG: </td> <td> <%out.println(dEG);%> </td> <tr>
	    <td>Line FG: </td> <td> <%out.println(dFG);%> </td> <tr>
	    <td>Angle e: </td> <td> <%out.println(dAngE);%> </td> <tr>
	    <td>Angle f: </td> <td> <%out.println(dAngF);%> </td> <tr>
	    <td>Angle g: </td> <td> <%out.println(dAngG);%> </td> <tr>
	  </tr>
    </table>
   <%}}
	 %>
	 
  </div>
  </body>

</html>

<%!
 public static Double TryToParse(String s){
	try{
      return Double.parseDouble(s);
	  }
	catch(NumberFormatException e){
	  return 0.0;
	  }
 }
 %>