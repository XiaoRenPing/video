<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>视频浏览</title>
  	<link href="${pageContext.request.contextPath }/style/js/player/video-js.css" rel="stylesheet">
    <script src="${pageContext.request.contextPath }/style/js/player/ie8/video-ie8.js"></script>
    <script src="${pageContext.request.contextPath }/style/js/player/video.js"></script>
   		 <!--[if IE]>
		    <style type="text/css">
			    	#scrollDiv1{
			    		display:none;
			    	}
		    </style>
    	<![endif]-->
</head>
<body>
	<div>
		<h3>java输入输出流方式</h3>
		<br/>
		<span>先通过java后台获取视频流数据，再通过整理输出到前端</span>
		
		
		<div id="scrollDiv1" style="width:800px;height:600px;">
			 <video id="example_video_1" class="video-js vjs-default-skin" controls preload=true width="640" height="480" data-setup="{}">       
			  	<source src="rtmp://192.168.1.131/live/" type="rtmp/flv"/>      
			 </video> 
		</div>
		<!--[if IE]>
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
		<![endif]-->
	</div>
	<div>
		<a href="">拍照/截图</a>
		<hr/>
		<h3>拍照列表</h3>
		<table>
			<tr>
				<td>序号</td>
				<td>名称</td>
				<td>时间</td>
				<td>操作</td>
			</tr>
			<tr>
				<td>1</td>
				<td>pic1</td>
				<td>2018-10-10</td>
				<td><a href="">预览</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
			<tr>
				<td>2</td>
				<td>pic2</td>
				<td>2018-01-10</td>
				<td><a href="">预览</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
		</table>
	</div>
	<div>
		<a href="">录像</a>
		<hr/>
		<h3>录像列表</h3>
		<table>
			<tr>
				<td>序号</td>
				<td>名称</td>
				<td>时长</td>
				<td>操作</td>
			</tr>
			<tr>
				<td>1</td>
				<td>test</td>
				<td>2min</td>
				<td><a href="">播放</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
			<tr>
				<td>2</td>
				<td>test2</td>
				<td>12min</td>
				<td><a href="">播放</a>&nbsp;&nbsp;<a href="">下载</a></td>
			</tr>
		</table>
	</div>
</body>
</html>