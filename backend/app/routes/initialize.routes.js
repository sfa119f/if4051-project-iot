module.exports = app => {
    
    const initialize = require("../controllers/initialize.controller.js");
  
    app.get("/initialize", initialize.requestToSystem);
};