module.exports = app => {
    const parkir = require("../controllers/parkir.controller.js");
    
    app.get("/parkir", parkir.getAll);
    app.get("/parkir/:datetime", parkir.getData);

};