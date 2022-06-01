module.exports = app => {
    const presensi = require("../controllers/presensi.controller.js");
  
    app.get("/presensi", presensi.getAll);
    app.get("/presensi/:matkul/:kelas", presensi.getData);

};