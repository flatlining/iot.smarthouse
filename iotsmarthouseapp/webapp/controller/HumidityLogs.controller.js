sap.ui.define([
	"co/schertel/iot/smarthouse/controller/BaseController",
	"co/schertel/iot/smarthouse/model/formatter"
], function(Controller, formatter) {
	"use strict";

	return Controller.extend("co.schertel.iot.smarthouse.controller.HumidityLogs", {
		formatter: formatter,

		onInit: function() {
			var oRouter = sap.ui.core.UIComponent.getRouterFor(this);
			oRouter.getRoute(this.HUMIDITY_LOGS).attachPatternMatched(this._onObjectMatched, this);
		},

		goToHumidityChart: function(oEvent) {
			this.navTo(this.HUMIDITY_CHART);
		},

		_onObjectMatched: function(oEvent) {
			// workaroung, this is called everytime the view is displayed. f* ugly!
			this.startModelAutoRefresh();
		}
	});
});