<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频预览</title>
</head>
<body>
	<h3>视频列表(摄像头接口)</h3>
	<table>
		<tr>
			<td>编号</td>
			<td>设备名称</td>
			<td>预览</td>
		</tr>
		<c:forEach items="${devIntefaceList }" var="dev">
			<tr>
				<td>${dev.devId }</td>
				<td>${dev.devName }</td>
				<td><a href="${pageContext.request.contextPath }/dev/lvcviewer?iChannelNum=${dev.devId }">预览</a></td>
			</tr>
		</c:forEach>
	</table>
	
</body>
</html>