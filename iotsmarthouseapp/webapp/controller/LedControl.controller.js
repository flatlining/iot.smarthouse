sap.ui.define([
	"co/schertel/iot/smarthouse/controller/BaseController"
], function(Controller) {
	"use strict";

	return Controller.extend("co.schertel.iot.smarthouse.controller.LedControl", {
		changeLedState: function(oEvent) {
			var ledId = parseInt(oEvent.getSource().data("ledId"));
			console.log("ledId " + ledId);

			var jsonBody = {
				"method": "mqtt",
				"sender": "iotsmarthouseapp",
				"messageType": "<TODO:iotSrvMessageTypeLedControl>",
				"messages": [{
					"lightId": ledId
				}]
			};

			var oModel = new sap.ui.model.json.JSONModel();
			oModel.loadData(
				"/destinations/iotmms/push/<TODO:iotSrvDeviceId>",
				JSON.stringify(jsonBody),
				true,
				"POST",
				null,
				false, {}
			);
		}
	});
});
