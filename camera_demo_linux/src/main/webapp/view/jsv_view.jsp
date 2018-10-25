<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
<link href="/style/js/player/video-js.css" rel="stylesheet" type="text/css">
<script src="/style/js/player/ie8/jquery-1.7.1.min.js"></script>
<script src="/style/js/player/ie8/videojs-ie8.js"></script>

</head>
<body>
	<div>
		<h3>本方法是通过本地安装LVC软件，只支持IE/Firefox浏览器</h3>
		<div id="scrollDiv">
			<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc' events='false' width="720" height="410">
			    <param name='mrl' value='rtsp://admin:zc123456@192.168.1.64:554/h264/ch1/main/av_stream' />
			    <param name='volume' value='50' />
			    <param name='autoplay' value='true' />
			    <param name='loop' value='false' />
			    <param name='fullscreen' value='false' />
			    <param name='controls' value='false' />
			</object>
		</div>
	</div>
</body>
</html>