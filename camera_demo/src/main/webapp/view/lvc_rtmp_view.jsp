<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
</head>
<body>
	<div>
		<h3>本方法是通过本地安装LVC软件，只支持IE/Firefox浏览器</h3>
		<div id="scrollDiv">
			<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc' events='false' width="720" height="410">
			    <param name='mrl' value='rtmp://192.168.1.131/live/chanel0' />
			    <param name='volume' value='50' />
			    <param name='autoplay' value='true' />
			    <param name='loop' value='false' />
			    <param name='fullscreen' value='false' />
			    <param name='controls' value='false' />
			</object>
			
			<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc1' events='false' width="720" height="410">
			    <param name='mrl' value='rtmp://192.168.1.131/live/chanel1' />
			    <param name='volume' value='50' />
			    <param name='autoplay' value='true' />
			    <param name='loop' value='false' />
			    <param name='fullscreen' value='false' />
			    <param name='controls' value='false' />
			</object>
			
			<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc2' events='false' width="720" height="410">
			    <param name='mrl' value='rtmp://192.168.1.131/live/chanel2' />
			    <param name='volume' value='50' />
			    <param name='autoplay' value='true' />
			    <param name='loop' value='false' />
			    <param name='fullscreen' value='false' />
			    <param name='controls' value='false' />
			</object>
			
			<object type='application/x-vlc-plugin' pluginspage="http://www.videolan.org/" id='vlc3' events='false' width="720" height="410">
			    <param name='mrl' value='rtmp://192.168.1.131/live/chanel3' />
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