<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
	<link href="${pageContext.request.contextPath }/style/js/player/video-js.css" rel="stylesheet" type="text/css">
	<script src="${pageContext.request.contextPath }/style/js/player/ie8/videojs-ie8.min.js"></script>
	<!-- <link href="http://vjs.zencdn.net/5.20.1/video-js.css" rel="stylesheet">-->
</head>
<body>
	<div>
		<h3>java输入输出流方式</h3>
		<br/>
		<span>先通过java后台获取视频流数据，再通过整理输出到前端</span>
		<div id="scrollDiv" style="width:800px;height:600px;">
			<video id="example_video_1" class="video-js vjs-default-skin" controls preload="auto" width="1280" height="720" poster="http://vjs.zencdn.net/v/oceans.png" data-setup="{}">
		    	<!-- <source src="1.mp4" type="video/mp4"> -->
			    <source src="rtmp://192.168.1.131/live/" type="rtmp/flv">
			</video>
		    <script src="${pageContext.request.contextPath }/style/js/player/video.js"></script>
		</div>
		
	</div>
</body>
</html>