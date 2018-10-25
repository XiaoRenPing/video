package com.vtsp.camera.config;

import com.sun.jna.NativeLong;

/**
 * 设备信息实体类
 * @author 肖仁枰(Alex Ping)
 *
 */
public class CameraInfoEntity {

	private NativeLong channel;
	
	private String cameraIP;
	
	private int cameraPort;
	
	private String userName;
	
	private String userPwd;
	
	private NativeLong userId;

	public NativeLong getChannel() {
		return channel;
	}

	public void setChannel(NativeLong channel) {
		this.channel = channel;
	}

	public String getCameraIP() {
		return cameraIP;
	}

	public void setCameraIP(String cameraIP) {
		this.cameraIP = cameraIP;
	}

	public int getCameraPort() {
		return cameraPort;
	}

	public void setCameraPort(int cameraPort) {
		this.cameraPort = cameraPort;
	}

	public String getUserName() {
		return userName;
	}

	public void setUserName(String userName) {
		this.userName = userName;
	}

	public String getUserPwd() {
		return userPwd;
	}

	public void setUserPwd(String userPwd) {
		this.userPwd = userPwd;
	}

	public NativeLong getUserId() {
		return userId;
	}

	public void setUserId(NativeLong userId) {
		this.userId = userId;
	}

}
