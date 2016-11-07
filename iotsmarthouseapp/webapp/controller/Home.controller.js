sap.ui.define([
	"co/schertel/iot/smarthouse/controller/BaseController"
], function(Controller) {
	"use strict";

	return Controller.extend("co.schertel.iot.smarthouse.controller.Home", {
		onTilePress: function(oEvent) {
			var targetRoute = oEvent.getSource().data("targetRoute");
			this.navTo(targetRoute);
		}
	});
});