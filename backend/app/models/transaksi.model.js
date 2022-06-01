const sql = require("./db.js");

// constructor
const Transaksi  = function(transaksi) {
  this.id = transaksi.id;
  this.waktu = transaksi.waktu;
  this.kelas = transaksi.kelas;
};

Transaksi.getAll = (result) => {
	sql.query("SELECT * FROM transaksi",(err,res)=>{
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};

Transaksi.getData = (datetime,result) => {
	console.log(datetime)
	var to_date = new Date(String(datetime).substring(2,6), String(datetime).substring(0,2));
	str_date = `${String(to_date.getFullYear())}-${String(to_date.getMonth()).padStart(2, '0')}`
	console.log(to_date, str_date)

	sql.query(`SELECT date_format(time, '%Y-%m') as month,
				id,
				SUM(amount) AS pengeluaran
			FROM transaksi 
			WHERE date_format(time, '%Y-%m') = "${str_date}"
			GROUP BY id,date_format(time, '%Y-%m')`,(err,res)=>{
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};


module.exports = Transaksi;