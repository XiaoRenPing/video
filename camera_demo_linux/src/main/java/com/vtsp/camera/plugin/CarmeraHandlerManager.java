package com.vtsp.camera.plugin;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.UUID;

import javax.swing.tree.DefaultMutableTreeNode;

import com.sun.jna.NativeLong;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.IntByReference;
import com.sun.jna.ptr.NativeLongByReference;
import com.vtsp.camera.config.CameraInfoEntity;
import com.vtsp.camera.config.FTPUtils;
import com.vtsp.camera.plugin.HCNetSDK.FMSGCallBack;
import com.vtsp.camera.plugin.HCNetSDK.NET_DVR_DEVICEINFO_V30;
import com.vtsp.camera.plugin.HCNetSDK.NET_DVR_IPPARACFG;
import com.vtsp.camera.plugin.HCNetSDK.NET_DVR_JPEGPARA;
import com.vtsp.camera.plugin.HCNetSDK.NET_DVR_WORKSTATE_V30;

/**
 * 摄像头操作封装类
 * 	  支持的操作：
 * 		
 * 		(1) 获取摄像头通道数量
 * 		(2) 预览流转换
 * 				启动线程转换  rtsp转 rtmp直播流
 * 		(2)	摄像头拍照
 * 		(3) 摄像头录像
 * 				获取视频流，保存mp4文件到本地
 * @author Administrator
 *
 */
public class CarmeraHandlerManager {

	static HCNetSDK hCNetSDK = HCNetSDK.INSTANCE;
    //static PlayCtrl playControl = PlayCtrl.INSTANCE;

    public static NativeLong g_lVoiceHandle;
        
    static HCNetSDK.NET_DVR_DEVICEINFO_V30 m_strDeviceInfo;
    static HCNetSDK.NET_DVR_IPPARACFG_V40  m_strIpparaCfg;
    HCNetSDK.NET_DVR_CLIENTINFO m_strClientInfo;

    boolean bRealPlay;
    String m_sDeviceIP;
    NativeLong lUserID;
    NativeLong lPreviewHandle;
    NativeLongByReference m_lPort;
    
    NativeLong lAlarmHandle;
    NativeLong lListenHandle;
    
    FMSGCallBack fMSFCallBack;
    //FRealDataCallBack fRealDataCallBack;

    static int m_iTreeNodeNum;
    
    DefaultMutableTreeNode m_DeviceRoot;
    
	/**
	 * 获取摄像头通道接口
	 * 
	 * @param lUserID  用户登录设备后返回的id
	 * @return devInterfaceList
	 */
	public static List<DeviceInterfaceEntity> findCameraDevInterfaceChannels(CameraInfoEntity cameraInfoEntity){
		List<DeviceInterfaceEntity> intList = new ArrayList<DeviceInterfaceEntity>();
		
		HCNetSDK sdk = HCNetSDK.INSTANCE;
        if (!sdk.NET_DVR_Init()) {
        	throw new RuntimeException("设备初始化获取失败");
        }

        NET_DVR_DEVICEINFO_V30 devinfo = new NET_DVR_DEVICEINFO_V30();// 设备信息

        NativeLong id = sdk.NET_DVR_Login_V30(cameraInfoEntity.getCameraIP(), (short) cameraInfoEntity.getCameraPort(), cameraInfoEntity.getUserName(), cameraInfoEntity.getUserPwd(), devinfo);
        cameraInfoEntity.setUserId(id);
        if (id.longValue() < 0) {
        	throw new RuntimeException("设备注册失败");
        } else {
            System.out.println("用户id" + id);
        }
        NET_DVR_WORKSTATE_V30 devwork = new NET_DVR_WORKSTATE_V30();
        if (!sdk.NET_DVR_GetDVRWorkState_V30(id, devwork)) {
        	throw new RuntimeException("返回设备状态失败");
        }

        IntByReference ibrBytesReturned = new IntByReference(0);// 获取IP接入配置参数
        NET_DVR_IPPARACFG ipcfg = new NET_DVR_IPPARACFG();
        ipcfg.write();
        Pointer lpIpParaConfig = ipcfg.getPointer();
        sdk.NET_DVR_GetDVRConfig(cameraInfoEntity.getUserId(), HCNetSDK.NET_DVR_GET_IPPARACFG, new NativeLong(0),
                lpIpParaConfig, ipcfg.size(), ibrBytesReturned);
        ipcfg.read();
        System.out.print("IP地址:" + cameraInfoEntity.getCameraIP());
        System.out.println("|设备状态：" + devwork.dwDeviceStatic);// 0正常，1CPU占用率过高，2硬件错误，3未知

        // 显示模拟通道
        for (int i = 1; i <= devinfo.byChanNum; i++) {
            System.out.print("Camera" + i + 1);// 模拟通道号名称
            System.out.print("|是否录像:" + devwork.struChanStatic[i].byRecordStatic);// 0不录像，不录像
            System.out.print("|信号状态:" + devwork.struChanStatic[i].bySignalStatic);// 0正常，1信号丢失
            System.out.println("|硬件状态:" + devwork.struChanStatic[i].byHardwareStatic);// 0正常，1异常
            
            DeviceInterfaceEntity dif = new DeviceInterfaceEntity();
            dif.setDevId(i);
            dif.setDevName("int" + i);
            intList.add(dif);
        }
        sdk.NET_DVR_Logout(cameraInfoEntity.getUserId());
        sdk.NET_DVR_Cleanup();
		return intList;
	}
	
	
	
	/**
	 * 拍照功能
	 * @param CameraInfoEntity cameraInfoEntity  设备初始化注册参数
	 * @return path   返回ftp文件路径
	 * @throws org.bytedeco.javacv.FrameRecorder.Exception
	 * @throws Exception
	 */
	public static String cameraTakePhoto(CameraInfoEntity cameraInfoEntity) throws Exception {
			//初始化设备
	        long startTime = System.currentTimeMillis();
	        HCNetSDK sdk = HCNetSDK.INSTANCE;
	        if (!sdk.NET_DVR_Init()) {
	           throw new RuntimeException("设备初始化获取失败");
	        }
	 
	        NET_DVR_DEVICEINFO_V30 devinfo = new NET_DVR_DEVICEINFO_V30();
	        
	        //设备注册
	        NativeLong id = sdk.NET_DVR_Login_V30(cameraInfoEntity.getCameraIP(), (short) cameraInfoEntity.getCameraPort(), cameraInfoEntity.getUserName(), cameraInfoEntity.getUserPwd(), devinfo);
	        if (id.longValue() < 0) {
	        	throw new RuntimeException("设备注册失败");
	        } 
	        System.out.println("设备注册成功，用户id" + id);
	        NET_DVR_WORKSTATE_V30 devwork = new NET_DVR_WORKSTATE_V30();
	        if (!sdk.NET_DVR_GetDVRWorkState_V30(id, devwork)) {
	        	// 返回Boolean值，判断是否获取设备能力
	        	throw new RuntimeException("返回设备状态失败");
	        }
	        startTime = System.currentTimeMillis();
	        //截屏对象
	        NET_DVR_JPEGPARA jpeg = new NET_DVR_JPEGPARA();
	        // 设置图片的分辨率
	        jpeg.wPicSize = 2;
	        // 设置图片质量
	        jpeg.wPicQuality = 2;
	 
	        IntByReference reference = new IntByReference();
	        ByteBuffer jpegBuffer = ByteBuffer.allocate(1024 * 1024);
	        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
	       // String fileNameString = "D:/CapturePicture/"+sdf.format(date)+ "_"+ cameraInfoEntity.getChannel() +".jpg";
	        String fileNameString = "cameracut_" + UUID.randomUUID().toString().replaceAll("-", "").toUpperCase() + sdf.format(new Date())+ "_"+ cameraInfoEntity.getChannel() +".jpg";
	        //声明文件
	        File file = new File(fileNameString);
	        //boolean is = sdk.NET_DVR_CaptureJPEGPicture_NEW(id, cameraInfoEntity.getChannel(), jpeg, jpegBuffer, 1024 * 1024, reference);
	        boolean is = sdk.NET_DVR_CaptureJPEGPicture_NEW(id, cameraInfoEntity.getChannel(), jpeg, jpegBuffer, 1024 * 1024, reference);
	        System.out.println("拍照获取图片用时" + (System.currentTimeMillis() - startTime) + "ms]");
	        System.out.println("拍照文件大小" + reference.getValue());
            BufferedOutputStream outputStream = null;
            try {
                outputStream = new BufferedOutputStream(new FileOutputStream(file));
                outputStream.write(jpegBuffer.array(), 0, reference.getValue());
                outputStream.flush();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                if (outputStream != null) {
                    try {
                        outputStream.close();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
            
            InputStream inputStream = new BufferedInputStream(new FileInputStream(file));
            boolean upload = FTPUtils.ftpUpload("img.xc580.net", 21, "eGpZyE38rG0ExkGv", "Kq8J6GrTt1ngJ0HKeJ", "/vtsp/imgs", file.getName(), inputStream);
            System.out.println("图片上传ftp,状态===========>" + upload);
            
            //删除图片文件
            if(file.exists() && file.isFile()) {
            	file.deleteOnExit();
            }
            inputStream.close();
            
            sdk.NET_DVR_Logout(id);
	        sdk.NET_DVR_Cleanup();
	        
	        if (is) {
	    		return "http://"+ "img.xc580.net" + "/vtsp/imgs/" +file.getName();
	        } else {
	        	return null;
	        }
	}

	
	/**
	 * 登录到设备
	 * @param username
	 * @param password
	 * @param ipaddress
	 * @param port
	 * @return
	 */
	public int deviceRegister(String username, String password, String ipaddress, int port) {
		NativeLong lUserID = hCNetSDK.NET_DVR_Login_V30(ipaddress, (short) port, username, password, m_strDeviceInfo);
		if(lUserID.longValue() == -1) {
			return 3; //注册失败
		}
		return 0;
	}
	

	public static void main(String[] args) throws Exception {
		CameraInfoEntity mci = new CameraInfoEntity();
		mci.setChannel(new NativeLong(1));
		mci.setCameraIP("192.168.1.64");
		mci.setCameraPort(8000);
		mci.setUserName("admin");
		mci.setUserPwd("zc123456");
		cameraTakePhoto(mci);
	}
}
