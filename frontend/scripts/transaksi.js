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
    for (let i = 0; i < month; i++) {
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
      "< 250 rb",
      "250 - 300 rb",
      "300 - 350 rb",
      "350 - 400 rb",
      "> 400 rb",
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

async function getDataTransaksi(year, month) {
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
  if (!monthTransaksi || !yearTransaksi) {
    alert("Isi tahun dan/atau bulan dengan benar!");
  } else {
    monthTransaksi =
      monthTransaksi < 10 ? "0" + monthTransaksi : monthTransaksi;
    const link = `http://localhost:8080/transaksi/${monthTransaksi}${yearTransaksi}`;
    let data = await getRequest(link);
    const newYValue = [0, 0, 0, 0, 0];
    for (let i = 0; i < data.length; i++) {
      if (data[i].pengeluaran < 250000) {
        newYValue[0]++;
      } else if (
        data[i].pengeluaran >= 250000 &&
        data[i].pengeluaran > 300000
      ) {
        newYValue[1]++;
      } else if (
        data[i].pengeluaran >= 300000 &&
        data[i].pengeluaran > 350000
      ) {
        newYValue[2]++;
      } else if (
        data[i].pengeluaran >= 350000 &&
        data[i].pengeluaran > 400000
      ) {
        newYValue[3]++;
      } else newYValue[4]++;
    }
    transaksiChart.data.datasets[0].data = newYValue;
    transaksiChart.data.datasets[0].sumData = data.length;
    transaksiChart.update();
  }
}
