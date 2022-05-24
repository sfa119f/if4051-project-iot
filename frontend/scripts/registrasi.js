function getUid() {
  // scan card and get uid
  document.getElementById("inputUid").value = "abcdefg";
}

function registrasi() {
  const uid = document.getElementById("inputUid").value;
  const nama = document.getElementById("inputNama").value;
  const nim = document.getElementById("inputNim").value;

  console.log(uid, nama, nim);
  if (!uid || !nama || !nim) {
    alert("Isi UID, Nama, dan/atau NIM dengan benar!");
  } else {
    // post data
    alert("Berhasil registrasi kartu ke database!");

    document.getElementById("inputUid").value = "";
    document.getElementById("inputNama").value = "";
    document.getElementById("inputNim").value = "";
  }
}
