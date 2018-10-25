<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
  	
</head>
<body>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/swf/swfobject.js"></script>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/swf/ParsedQueryString.js"></script>
	<script type="text/javascript" src="${pageContext.request.contextPath }/style/js/streammedia/streamedian.js"></script>
			
	<div>
		<h3>java输入输出流方式</h3>
		<br/>
		<span>先通过java后台获取视频流数据，再通过整理输出到前端</span>
		
		<div id="scrollDiv">
			<div id="GrindPlayer"></div>
			<!-- <br>
				<input id="userInput" value="rtmp://192.168.1.131/live/" size="80"> 
				<button onclick="userSubmit()">预览流</button><br>
			<p> -->
			<!-- <script type="text/javascript">
				function userSubmit() {
				  window.location = getlink(document.getElementById('userInput').value);
				}
			</script> -->
		</div>
	</div>
	
	<div>
		<a href="${pageContext.request.contextPath }/dev/takephoto?chanel=1">拍照/截图</a>
		<hr/>
		<h3>拍照列表</h3>
		<video id="test_video" controls autoplay>
		    <source src="rtsp://admin:abc12345@59.47.53.210:554/h264/ch1/main/av_stream" type="application/x-rtsp">
		</video>
	</div>
</body>
</html>