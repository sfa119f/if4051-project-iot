const sql = require("./db.js");

// constructor
const Presensi  = function(presensi) {
  this.id = presensi.id;
  this.waktu = presensi.waktu;
  this.kelas = presensi.kelas;
};

Presensi.getAll = (result) => {
	sql.query("SELECT * FROM presensi",(err,res)=>{
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};

Presensi.getData = (matkul,kelas,result) => {
	console.log(`Get presensi data from maetkul ${matkul} kelas ${kelas}`)
	sql.query(`SELECT matkul, kelas, date_format(time, '%Y-%m-%d') as date, COUNT(id) as jumlah FROM presensi WHERE matkul = "${matkul}" AND kelas = ${kelas} GROUP BY matkul, kelas, date_format(time, '%Y-%m-%d')`,(err,res) => {
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};

module.exports = Presensi;