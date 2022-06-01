function getUid() {
  // scan card and get uid
  document.getElementById("btnUid").disabled = true;
  document.getElementById("spinUid").hidden = false;
  document.getElementById("succesUid").hidden = false;
  document.getElementById("failUid").hidden = false;
  document.getElementById("inputUid").value = "abcdefg";
}

function getFingerPrint() {
  // scan fingerPrint and get data
  document.getElementById("btnFinger").disabled = true;
  document.getElementById("spinFinger").hidden = false;
  document.getElementById("succesFinger").hidden = false;
  document.getElementById("failFinger").hidden = false;
  document.getElementById("inputFingerprint").value = 1;
}

function registrasi() {
  const uid = document.getElementById("inputUid").value;
  const finger = document.getElementById("inputFingerprint").value;
  const nama = document.getElementById("inputNama").value;
  const nim = document.getElementById("inputNim").value;

  console.log(uid, nama, nim);
  if (!uid || !finger || !nama || !nim) {
    alert("Isi UID, Fingerprint, Nama, dan/atau NIM dengan benar!");
  } else {
    // post data
    alert("Berhasil registrasi kartu ke database!");

    document.getElementById("inputUid").value = "";
    document.getElementById("inputFingerprint").value = "";
    document.getElementById("inputNama").value = "";
    document.getElementById("inputNim").value = "";
  }
}
