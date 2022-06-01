const Initialize = require("../models/initialize.model.js");

exports.requestToSystem = (req,res) =>  {
    console.log('routing to initialize page')
	Initialize.requestToSystem((err,data) => {
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
	Initialize.getData(req.params.datetime,(err,data) => {
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
