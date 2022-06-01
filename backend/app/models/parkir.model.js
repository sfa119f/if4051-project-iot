const sql = require("./db.js");

// constructor
const Parkir  = function(parkir) {
  this.id = parkir.id;
  this.waktu = parkir.waktu;
  this.kelas = parkir.kelas;
};

Parkir.getAll = (result) => {
	// var current_time = new Date().getHours(); 
	// console.log(current_time)
	sql.query("SELECT date_format(jam, '%Y-%m-%d- %H' ) as jam, jumlah FROM parkir_per_hour",(err,res)=>{
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};

Parkir.getData = (datetime,result) => {
	var to_date = new Date(String(datetime).substring(4,8), parseInt(String(datetime).substring(2,4)), parseInt(String(datetime).substring(0,2)));
	console.log(to_date)
	var current_time = new Date()
	current_time.setHours(current_time.getHours() + 7)
	console.log(current_time)
	if (to_date != current_time){
		str = ''
		for (i = 0;i<=24;i++){
			if (i < 10){
				jam = `0${i}`
			} else {
				jam = String(i)
			}
			jam_query = 
			str += `SELECT "${String(to_date.getFullYear())}-${String(to_date.getMonth()).padStart(2, '0')}-${String(to_date.getDate()).padStart(2, '0')} ${jam}" AS hour,
					sum(is_parkir) AS jumlah                          
					FROM parkir                                                                                          
					WHERE date_format(time, '%Y-%m-%d %H') <= STR_TO_DATE("${String(to_date.getFullYear())}-${String(to_date.getMonth())}-${String(to_date.getDate()).padStart(2, '0')} ${jam}",'%Y-%m-%d %H')`
			if (i != 24){
				str += ' UNION '
			}
		}
	} else {
		str = ''
		for (i = 0;i<=current_time.getHours();i++){
			if (i < 10){
				jam = `0${i}`
			} else {
				jam = String(i)
			}
			// console.log(`${String(to_date.getFullYear())}-${String(to_date.getMonth())}-${String(to_date.getDate()).padStart(2, '0')} ${jam}`)
			str += `SELECT "${String(to_date.getFullYear())}-${String(to_date.getMonth())}-${String(to_date.getDate()).padStart(2, '0')} ${jam}" AS hour,
					sum(is_parkir) AS jumlah                          
					FROM parkir                                                                                          
					WHERE date_format(time, '%Y-%m-%d %H') <= STR_TO_DATE("${String(to_date.getFullYear())}-${String(to_date.getMonth())}-${String(to_date.getDate()).padStart(2, '0')} ${jam}",'%Y-%m-%d %H')`
			if (i != 24){
				str += ' UNION '
			}
		}
		console.log(str)
	}

	sql.query(str,(err,res)=>{
		if(err){
			console.log("error: ",err);
			result(err,null);
			return;
		}
		result(null,res);
		return;
	});
};


module.exports = Parkir;