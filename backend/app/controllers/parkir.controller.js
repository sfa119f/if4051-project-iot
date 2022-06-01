const Parkir = require("../models/parkir.model.js");

exports.getAll = (req,res) =>  {
	console.log('routing to parkir page')
	Parkir.getAll((err,data) => {
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
	Parkir.getData(req.params.datetime,(err,data) => {
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
