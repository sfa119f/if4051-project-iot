module.exports = app => {
    const transaksi = require("../controllers/transaksi.controller.js");
  
    app.get("/transaksi", transaksi.getAll);
    app.get("/transaksi/:datetime", transaksi.getData);

};