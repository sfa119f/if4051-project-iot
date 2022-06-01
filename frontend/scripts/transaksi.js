const optYear = document.getElementById("yearTransaksi");
let year = new Date().getFullYear();
for (let i = 2; i >= 0; i--) {
  const opt = document.createElement("option");
  opt.text = year - i;
  opt.value = year - i;
  optYear.add(opt);
}

const optMonth = document.getElementById("monthTransaksi");
optYear.addEventListener("input", function (evt) {
  optMonth.value = "";
  while (optMonth.options.length > 1) {
    optMonth.remove(1);
  }
  if (optYear.value == new Date().getFullYear()) {
    let month = new Date().getMonth();
    for (let i = 0; i <= month; i++) {
      const opt = document.createElement("option");
      opt.text = i + 1;
      opt.value = i + 1;
      optMonth.add(opt);
    }
  } else {
    for (let i = 0; i < 12; i++) {
      const opt = document.createElement("option");
      opt.text = i + 1;
      opt.value = i + 1;
      optMonth.add(opt);
    }
  }
});

const transaksiChart = new Chart("transaksiChart", {
  type: "pie",
  data: {
    labels: [
      "< 250 jt",
      "250 - 300 jt",
      "300 - 350 jt",
      "350 - 400 jt",
      "> 400 jt",
    ],
    datasets: [
      {
        backgroundColor: [blue2, blue3, orange1, orange2, orange3],
        data: [0, 0, 0, 0, 0],
        sumData: 0,
        // data: [0, 0, 0, 0, 0],
        // sumData: 0,
      },
    ],
  },
  options: {
    tooltips: {
      callbacks: {
        // title: function (tooltipItem, data) {
        //   return data.labels[tooltipItem[0].index];
        // },
        // label: function (tooltipItem, data) {
        //   return data.datasets[0].data[tooltipItem.index];
        // },
        afterLabel: function (tooltipItem, data) {
          var dataset = data.datasets[0];
          var percent = (
            (dataset.data[tooltipItem.index] / dataset.sumData) *
            100
          ).toFixed(2);
          return "(" + percent + "%)";
        },
      },
    },
    plugins: {
      datalabels: {
        formatter: (value, ctx) => {
          const sumData = ctx.chart.data.datasets[0].sumData;
          let temp = ((value * 100) / sumData).toFixed(2);
          if (temp < 10) return "";
          else return temp + "%";
        },
        color: "#fff",
      },
    },
  },
});

function getDataTransaksi(year, month) {
  let monthTransaksi, yearTransaksi;
  if (year && month) {
    monthTransaksi = month;
    yearTransaksi = year;
    document.getElementById("monthTransaksi").value = month;
    document.getElementById("yearTransaksi").value = year;
  } else {
    monthTransaksi = document.getElementById("monthTransaksi").value;
    yearTransaksi = document.getElementById("yearTransaksi").value;
  }
  console.log("monthTransaksi", monthTransaksi);
  console.log("yearTransaksi", yearTransaksi);
  if (!monthTransaksi || !yearTransaksi) {
    alert("Isi tahun dan/atau bulan dengan benar!");
  } else {
    const newYValue = [];
    let newSum = 0;
    while (newYValue.length != 5) {
      let temp = Math.floor(Math.random() * 51);
      newYValue.push(temp);
      newSum += temp;
    }
    transaksiChart.data.datasets[0].data = newYValue;
    transaksiChart.data.datasets[0].sumData = newSum;
    transaksiChart.update();
  }
}
