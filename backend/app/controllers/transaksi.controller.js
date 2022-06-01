const Transaksi = require("../models/transaksi.model.js");

exports.getAll = (req,res) =>  {
	Transaksi.getAll((err,data) => {
		if(err) {
			res.status(500).send({
	        	message: err.message || "Some error occurred while retrieving species."
	      });
		}
		else {
			res.status(200).send({
				data
			})
		};
	});
};

exports.getData = (req, res) => {
	Transaksi.getData(req.params.datetime,(err,data) => {
		if(err) {
			res.status(500).send({
	        message:
	          err.message || "Some error occurred while retrieving species."
	      });
		}
		else {
			res.status(200).send(data)
		}
	})
};
