package com.vtsp.camera.controller;

import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Properties;
import java.util.ResourceBundle;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.collections.CollectionUtils;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.servlet.ModelAndView;

import com.sun.jna.NativeLong;
import com.vtsp.camera.config.CameraInfoEntity;
import com.vtsp.camera.plugin.CarmeraHandlerManager;
import com.vtsp.camera.plugin.DeviceInterfaceEntity;

@Controller
@RequestMapping("/dev/*")
public class CameraController {

	/**
	 * 获取设备端口（摄像头个数）
	 * @return
	 */
	@RequestMapping(method=RequestMethod.GET, value="ints")
	public String getDeviceInterface(HttpServletRequest request) {
		ResourceBundle bundle = ResourceBundle.getBundle("device");
		
		CameraInfoEntity mci = new CameraInfoEntity();
		mci.setChannel(new NativeLong(1));
		mci.setCameraIP(bundle.getString("cameraip"));
		mci.setCameraPort(Integer.parseInt(bundle.getString("cameraport")));
		mci.setUserName(bundle.getString("username"));
		mci.setUserPwd(bundle.getString("password"));		
		
		List<DeviceInterfaceEntity> intList = CarmeraHandlerManager.findCameraDevInterfaceChannels(mci);
		
		request.setAttribute("intList", intList);
		return "index";
	}
	
	
	/**
	 * 预览【四个摄像头】
	 * @param channel
	 * @return
	 */
	@RequestMapping(method=RequestMethod.GET, value="index")
	public String preview(HttpServletRequest request) {
		
		ResourceBundle bundle = ResourceBundle.getBundle("device");
		
		CameraInfoEntity mci = new CameraInfoEntity();
		mci.setChannel(new NativeLong(1));
		mci.setCameraIP(bundle.getString("cameraip"));
		mci.setCameraPort(Integer.parseInt(bundle.getString("cameraport")));
		mci.setUserName(bundle.getString("username"));
		mci.setUserPwd(bundle.getString("password"));
		
		List<DeviceInterfaceEntity> intList = CarmeraHandlerManager.findCameraDevInterfaceChannels(mci);
		List<DeviceInterfaceEntity> devList = new ArrayList<DeviceInterfaceEntity>();
		if(!CollectionUtils.isEmpty(intList)) {
			for(int i=1; i<=intList.size(); ++i) {
				//拼接预览地址  [rtsp://admin:zc123456@192.168.1.64:554/h264/ch1/main/av_stream]
				DeviceInterfaceEntity dif = new DeviceInterfaceEntity();
				dif.setDevId(i);
				dif.setChannel(i);
				dif.setViewUrl("rtsp://"+mci.getUserName()+":"+mci.getUserPwd()+"@"+mci.getCameraIP()+":554/h264/ch"+i+"/main/av_stream");
				devList.add(dif);
			}
		}
		request.setAttribute("devList", devList);
		return "index";
	}
	
	@ResponseBody
	@RequestMapping(method=RequestMethod.GET, value="takepic")
	public String takePicture(@RequestParam("channel") Integer channel, HttpServletResponse resp) throws Exception {
		
		ModelAndView mv = new ModelAndView();
		/*CameraInfoEntity mci = new CameraInfoEntity();
		mci.setChannel(new NativeLong(1));
		mci.setCameraIP("192.168.1.64");
		mci.setCameraPort(8000);
		mci.setUserName("admin");
		mci.setUserPwd("zc123456");*/
		ResourceBundle bundle = ResourceBundle.getBundle("device");
		
		CameraInfoEntity mci = new CameraInfoEntity();
		mci.setChannel(new NativeLong(1));
		mci.setCameraIP(bundle.getString("cameraip"));
		mci.setCameraPort(Integer.parseInt(bundle.getString("cameraport")));
		mci.setUserName(bundle.getString("username"));
		mci.setUserPwd(bundle.getString("password"));
		String path = CarmeraHandlerManager.cameraTakePhoto(mci);
		System.out.println("图片已上传===========>"+path);
		return path;
	}
}
