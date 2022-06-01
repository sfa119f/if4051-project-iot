const blue1 = "#003049";
const blue2 = "#219EBC";
const blue3 = "#8ECAE6";
const orange1 = "#D62828";
const orange2 = "#FB8500";
const orange3 = "#FFB703";
// const spinner = document.getElementById("loading");

async function fetchWithTimeout(resource, options = {}) {
  const abortController = new AbortController();
  const id = setTimeout(() => abortController.abort(), options.timeout);
  const response = await fetch(resource, {
    ...options,
    signal: abortController.signal,
  });
  clearTimeout(id);
  return response;
}

async function getRequest(url, optTimeout = 1500) {
  // spinner.style.display = "flex !important";
  try {
    let res = await fetchWithTimeout(url, { timeout: optTimeout });
    // spinner.style.display = "none !important";
    if (res.ok) {
      return await res.json();
    } else {
      alert("HTTP-Error: " + response.status);
    }
  } catch (error) {
    // spinner.style.display = "none !important";
    console.error(error);
  }
}

async function postRequest(url, data, optTimeout = 1500) {
  const opt = {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(data),
    timeout: optTimeout,
  };
  // spinner.style.display = "flex !important";
  try {
    let res = await fetchWithTimeout(url, opt);
    // spinner.style.display = "none !important";
    if (res.ok) {
      return await res.json();
    } else {
      alert("HTTP-Error: " + response.status);
    }
  } catch (error) {
    // spinner.style.display = "none !important";
    console.error(error);
  }
}
