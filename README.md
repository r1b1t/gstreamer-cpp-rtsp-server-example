🇹🇷 Türkçe Açıklama:

Bu proje, GStreamer kütüphanesi kullanılarak C++ ile basit bir RTSP sunucusu geliştirmeyi göstermektedir.
Sunucu, test videosu üretir ve RTSP üzerinden yayınlar. Böylece istemciler (ör. VLC, FFPLAY) bağlanıp canlı olarak izleyebilir.

📂 İçerik:

RTSP Sunucusu Kurulumu:
Port 8554 üzerinde dinler.
Yayına şu adresten erişilebilir:
rtsp://127.0.0.1:8554/test


Medya Pipeline:
videotestsrc kullanarak test videosu üretir.
x264enc ile H.264 formatına düşük gecikmeli şekilde sıkıştırır.
rtph264pay ile RTP paketlerine dönüştürür.

Paylaşımlı Pipeline:
Aynı pipeline birden fazla istemci ile paylaşılır.
Bu sayede CPU/GPU daha az yüklenir.

🇬🇧 English Description:

This project demonstrates how to create a simple RTSP server in C++ using the GStreamer library.
The server generates a test video and streams it via RTSP so that clients (e.g., VLC, FFPLAY) can connect and view it in real time.

📂 Contents:

RTSP Server Setup:
Listens on port 8554.
Stream available at:
rtsp://127.0.0.1:8554/test

Media Pipeline:
Uses videotestsrc to generate a test video.
Encodes with x264enc in low-latency H.264 format.
Packetizes with rtph264pay for RTP streaming.

Shared Pipeline:
The same pipeline is shared between multiple clients.
This reduces CPU/GPU usage.
