//Test check_latency
#include <WiFiS3.h>
#include "commands.h"

void sendWebpage(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();

  client.println("<!DOCTYPE html>");
  client.println("<html><head><meta name='viewport' content='width=device-width, initial-scale=1'>");

  client.println("<style>");
  client.println("button{padding:20px;font-size:20px;margin:10px;}");
  client.println("</style></head><body>");

  //Überschrift gesamt
  client.println("<h1>VertiGo - Bedienpanel</h1>");
  //Überschrift Freigabe
  client.print("<p>Antriebsfreigabe <b>");
  // Zustand anzeigen
  client.print("<p>Status: <b>");
  client.print(enableMotors ? "FREIGEGEBEN" : "GESPERRT");
  client.println("</b></p>");

  // Buttons EIN/AUS
  client.println("<a href='/?motor=on'><button style='background:lightgreen;'>FREIGEBEN</button></a>");
  client.println("<a href='/?motor=off'><button style='background:salmon;'>SPERREN</button></a>");

  // Joystick
  client.println("<h2>Joystick</h2>");
  client.println("<div id='joyContainer'>");
  client.println("  <div id='joy'></div>");
  client.println("</div>");

  client.println("<style>");
  client.println("#joyContainer {");
  client.println("  width: 300px;");
  client.println("  height: 300px;");
  client.println("  background: #eee;");
  client.println("  border-radius: 50%;");
  client.println("  position: relative;");
  client.println("  touch-action: none;");
  client.println("  margin-top: 20px;");
  client.println("}");
  client.println("#joy {");
  client.println("  width: 60px;");
  client.println("  height: 60px;");
  client.println("  background: #ccc;");
  client.println("  border-radius: 50%;");
  client.println("  position: absolute;");
  client.println("  left: 50%;");             // ➜ 0-Stellung horizontal
  client.println("  top: 50%;");              // ➜ 0-Stellung vertikal
  client.println("  transform: translate(-50%, -50%);"); // exakte Zentrierung
  client.println("}");
  client.println("</style>");

  // JS für Live-Update
  //Joystick
  client.println("<script>");
  client.println("const joy = document.getElementById('joy');");
  client.println("const box = document.getElementById('joyContainer');");

  client.println("let active = false;");
  client.println("let boxRect = box.getBoundingClientRect();");

  client.println("let lastSendTime = 0;");
  client.println("const SEND_INTERVAL = 200");  // alle xy ms");

  client.println("function send(x, y, t) {"); //+ t
  client.println("  const now = Date.now();");
  client.println("  if (((x != 0) || (y != 0)) && now - lastSendTime < SEND_INTERVAL) return;");
  client.println("  lastSendTime = now;");
  client.println("  fetch(`/joy?x=${x}&y=${y}&t=${t}`);"); //Anpassung zum Testen + &t=${t}
  client.println("}");

  //---------------------------------------

  client.println("function handle(e) {");
  client.println("  if (!active) return;");
  client.println("  const touchTimeStamp = Math.round(performance.now());"); //Anpassung zum Testen

  client.println("  let x = e.clientX - boxRect.left - 150;");
  client.println("  let y = e.clientY - boxRect.top - 150;");

  client.println("  const dist = Math.sqrt(x*x + y*y);");
  client.println("  if (dist > 60) {");
  client.println("      x = x / dist * 60;");
  client.println("      y = y / dist * 60;");
  client.println("  }");

  client.println("  joy.style.left = (150 + x - 30) + 'px';");
  client.println("  joy.style.top  = (150 + y - 30) + 'px';");

  client.println("const rect = box.getBoundingClientRect();");
  client.println("const centerX = rect.width / 2;");
  client.println("const centerY = rect.height / 2;");

  client.println("joy.style.left = (centerX + x) + 'px';");
  client.println("joy.style.top  = (centerY + y) + 'px';");

  client.println("  const nx = (x / 60).toFixed(2);");
  client.println("  const ny = (-y / 60).toFixed(2);");

  client.println("  send(nx, ny, touchTimeStamp);"); //+ touchTimeStamp
  client.println("}");

  client.println("box.addEventListener('mousedown', e => { active = true; handle(e); });");
  client.println("window.addEventListener('mousemove', handle);");
  client.println("window.addEventListener('mouseup', () => { active = false; joy.style.left='45px'; joy.style.top='45px'; send(0,0); });");

  client.println("box.addEventListener('touchstart', e => { active = true; handle(e.touches[0]); });");
  client.println("window.addEventListener('touchmove', e => handle(e.touches[0]));");
  client.println("window.addEventListener('touchend', () => { active = false; joy.style.left='45px'; joy.style.top='45px'; send(0,0); });");

  client.println("</script>");
  client.println("</body></html>");
}