const Presensi = require("../models/presensi.model.js");

exports.getAll = (req,res) =>  {
	Presensi.getAll((err,data) => {
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
	Presensi.getData(req.params.matkul,req.params.kelas,(err,data) => {
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

