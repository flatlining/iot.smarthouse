sap.ui.define([
	"sap/ui/core/mvc/Controller",
	"sap/ui/core/routing/History"
], function(Controller, History) {
	"use strict";

	return Controller.extend("co.schertel.iot.smarthouse.controller.BaseController", {
		HOME: "home",
		HUMIDITY_CHART: "humidityChart",
		HUMIDITY_LOGS: "humidityLogs",
		TEMPERATURE_CHART: "temperatureChart",
		TEMPERATURE_LOGS: "temperatureLogs",

		refreshIntervalId: null,

		getRouter: function() {
			return sap.ui.core.UIComponent.getRouterFor(this);
		},

		navTo: function(routeName, dataToPass) {
			dataToPass = (typeof dataToPass === "undefined") ? {} : dataToPass;
			this.stopModelAutoRefresh();
			this.getRouter().navTo(routeName, dataToPass, false);
		},

		navToHome: function() {
			this.stopModelAutoRefresh();
			this.getRouter().navTo(this.HOME, {}, true);
		},

		navBack: function() {
			var history, previousHash;

			history = History.getInstance();
			previousHash = history.getPreviousHash();

			this.stopModelAutoRefresh();

			if (previousHash !== undefined) {
				window.history.go(-1);
			} else {
				this.getRouter().navTo(previousHash, {}, true);
			}
		},

		navBackTo: function(routeName, dataToPass) {
			dataToPass = (typeof dataToPass === "undefined") ? {} : dataToPass;
			this.stopModelAutoRefresh();
			this.getRouter().navTo(routeName, dataToPass, true);
		},

		startModelAutoRefresh: function() {
			var that = this;
			this.refreshIntervalId = setInterval(function() {
				that.getView().getModel().refresh(true);
			}, 1000);
		},

		stopModelAutoRefresh: function() {
			if (typeof this.refreshIntervalId !== "undefined") {
				clearInterval(this.refreshIntervalId);
				this.refreshIntervalId = null;
			}
		},
		refreshModel: function() {
			this.getView().getModel().refresh(true);
		}
	});
});