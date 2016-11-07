sap.ui.define([], function() {
	"use strict";
	return {
		deviceNameFromId: function(deviceId) {
			var deviceName = deviceId;
			var iotDevices = this.getView().getModel("iotDevices").getProperty("/");
			for (var i = 0; i < iotDevices.length; i++) {
				var iotDevice = iotDevices[i];
				if (iotDevice.id === deviceId) {
					deviceName = iotDevice.name;
					break;
				}
			}
			return deviceName;
		}
	};
});