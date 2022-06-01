const mk = document.getElementById("matkul");
const kls = document.getElementById("kelas");
const opt1 = document.createElement("option");
opt1.text = "K-1";
opt1.value = "1";
const opt2 = document.createElement("option");
opt2.text = "K-2";
opt2.value = "2";
const opt3 = document.createElement("option");
opt3.text = "K-3";
opt3.value = "3";
mk.addEventListener("input", function (evt) {
  kls.value = "";
  while (kls.options.length > 1) {
    kls.remove(1);
  }
  if (matkul.value == "bd") {
    kls.add(opt1);
    kls.add(opt2);
    kls.add(opt3);
  } else if (matkul.value == "ml") {
    kls.add(opt1);
    kls.add(opt2);
  } else if (matkul.value == "iot") {
    kls.add(opt1);
  }
});

const labels = [];
const jmlMahasiswa = [];
for (let i = 1; i <= 16; i++) {
  labels.push(i);
  // jmlMahasiswa.push(0);
  if (i == 1 || i == 8 || i == 16) jmlMahasiswa.push(50);
  else {
    const min = 40;
    const rand = Math.floor(Math.random() * 11);
    jmlMahasiswa.push(rand + min);
  }
}

const data = {
  labels: labels,
  datasets: [
    {
      label: "Jumlah Mahasiswa",
      data: [],
      borderColor: blue2,
      backgroundColor: blue3,
      lineTension: 0,
    },
  ],
};

const presensiChart = new Chart("presensiChart", {
  type: "line",
  data: data,
  options: {
    legend: {
      display: false,
    },
    scales: {
      xAxes: [
        {
          display: true,
          scaleLabel: {
            display: true,
            labelString: "Pertemuan",
          },
          // ticks: {
          //   autoSkip: false,
          //   callback: function (tick) {
          //     return tick.split(" ")[1];
          //   },
          // },
        },
      ],
      yAxes: [
        {
          display: true,
          scaleLabel: {
            display: true,
            labelString: "Jumlah Mahasiswa",
          },
          ticks: {
            beginAtZero: true,
            steps: 10,
            stepValue: 5,
            // max: 5,
          },
        },
      ],
    },
    tooltips: {
      callbacks: {
        title: function (tooltipItem, data) {
          return "Pertemuan " + data.labels[tooltipItem[0].index];
        },
      },
    },
    plugins: {
      datalabels: {
        display: false,
      },
    },
  },
});

async function getDataPresensi() {
  const matkul = document.getElementById("matkul").value.toUpperCase();
  const kelas = document.getElementById("kelas").value;
  if (!matkul || !kelas) {
    alert("Isi mata kuliah dan/atau kelas dengan benar!");
  } else {
    const link = `http://localhost:8080/presensi/${matkul}/${kelas}`;
    let data = await getRequest(link);
    const newJmlMahasiswa = [];
    for (let i = 0; i < data.length; i++) {
      newJmlMahasiswa.push(data[i].jumlah);
    }
    while (newJmlMahasiswa.length < 16) {
      newJmlMahasiswa.push(null);
    }
    presensiChart.data.datasets[0].data = newJmlMahasiswa;
    // presensiChart.options.scales.yAxes[0].ticks.max =
    //   Math.max(newJmlMahasiswa) + 5;
    presensiChart.update();
  }
}
