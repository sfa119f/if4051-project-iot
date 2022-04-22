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
      data: jmlMahasiswa,
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
            max: 55,
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

function getDataPresensi() {
  const matkul = document.getElementById("matkul").value;
  const kelas = document.getElementById("kelas").value;
  console.log("matkul", matkul);
  console.log("kelas", kelas);
  if (!matkul || !kelas) {
    alert("Isi mata kuliah dan/atau kelas dengan benar");
  } else {
    const newJmlMahasiswa = [];
    for (let i = 1; i <= 16; i++) {
      if (i == 1 || i == 8 || i == 16) newJmlMahasiswa.push(50);
      else {
        const min = 40;
        const rand = Math.floor(Math.random() * 11);
        newJmlMahasiswa.push(rand + min);
      }
    }
    presensiChart.data.datasets[0].data = newJmlMahasiswa;
    presensiChart.update();
  }
}
