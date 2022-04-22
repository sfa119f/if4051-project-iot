const labelParkir = [];
const jmlKendaraan = [];
for (let i = 0; i < 24; i++) {
  let temp = i < 10 ? "0" + i : i;
  labelParkir.push(`${temp}:00`);
  // jmlKendaraan.push(0);
  const min = 40;
  const rand = Math.floor(Math.random() * 11);
  jmlKendaraan.push(rand + min);
}

const dataParkir = {
  labels: labelParkir,
  datasets: [
    {
      label: "Jumlah Kendaraan",
      data: jmlKendaraan,
      borderWidth: 2,
      borderColor: blue2,
      backgroundColor: blue3,
      lineTension: 0,
    },
  ],
};

const parkirChart = new Chart("parkirChart", {
  type: "bar",
  data: dataParkir,
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
            labelString: "Waktu",
          },
        },
      ],
      yAxes: [
        {
          display: true,
          scaleLabel: {
            display: true,
            labelString: "Jumlah Kendaraan",
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
          return "Pukul " + data.labels[tooltipItem[0].index];
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

function getDataParkir() {
  const dateParkir = document.getElementById("dateParkir").value;
  console.log("dateParkir", dateParkir);
  if (!dateParkir) {
    alert("Isi tanggal dengan benar");
  } else {
    const newJmlKendaraan = [];
    while (newJmlKendaraan.length != 24) {
      const min = 40;
      const rand = Math.floor(Math.random() * 11);
      newJmlKendaraan.push(rand + min);
    }
    parkirChart.data.datasets[0].data = newJmlKendaraan;
    parkirChart.update();
  }
}
