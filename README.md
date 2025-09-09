# EC_PULSAR_VCU – Vehicle Control Unit

Bu proje, **Teknofest Efficiency Challenge** kapsamında geliştirilen **Pulsar Takımı Elektrikli Araç Kontrol Sistemi (VCU)** yazılımını içerir.  
Amaç, elektrikli aracın tüm alt sistemlerini yönetmek, güvenli sürüşü sağlamak ve yarış koşullarında verimliliği artırmaktır.

---

## Özellikler

- Araç Başlatma & Güvenlik Kontrolleri  
- Batarya Yönetim Sistemi (BMS) entegrasyonu (voltaj, akım, sıcaklık takibi)  
- Motor Sürücü ile Haberleşme (gaz pedalı → tork/akım komutu)  
- Yalıtım/Güvenlik İzleme (IMD, kontaktör kontrolü)  
- Veri Kaydı (SD kart entegrasyonu – opsiyonel)  
- Telemetri Desteği (araç–pit arası CAN/UART haberleşme)  
- Sürücü Girdi Yönetimi (gaz, fren, yön seçici)  
- Dengeleme & hata durumunda güvenli kapatma (fail-safe)  

---

##  Kullanılan Teknolojiler

- **Dil:** C / Embedded C  
- **MCU:** STM32 tabanlı VCU kartı  
- **Haberleşme:** CAN-Bus  
- **Ek Arayüzler:** SPI / UART / GPIO  
- **Dosya Sistemi:** FatFs (opsiyonel veri kaydı)  

---

## Kurulum & Çalıştırma

1. Projeyi **STM32CubeIDE / Keil / IAR** üzerinden açın.  
2. CAN pinlerini ve baud rate’i donanıma göre ayarlayın (örn. **500 kbps**).  
3. BMS ve Motor sürücü CAN ID’lerini `can_bus.c` içinde güncelleyin.  
4. Projeyi derleyip VCU kartına yükleyin.  

---

## Sistem Akışı

### Araç Açılış
- IMD ve BMS hazır → kontaktörler kapanır.  

### Sürüş
- Gaz pedalı → VCU → Motor sürücü (CAN üzerinden).  
- BMS sürekli izlenir, kritik durumda güç kesilir.  

### Veri Kaydı & Telemetri
- Sensör değerleri SD karta yazılır veya telemetriyle pit’e iletilir.  

### Kapatma
- Güvenli şekilde kontaktörler açılır.  

---

## Donanım Entegrasyonları

| Alt Sistem       | Haberleşme | Açıklama                      |
|------------------|------------|-------------------------------|
| **BMS**          | CAN-Bus    | Hücre voltaj, akım, sıcaklık  |
| **Motor Sürücü** | CAN-Bus    | Tork/akım komutları           |
| **IMD**          | GPIO       | Yalıtım hatası izleme         |
| **Pedal Sensörleri** | ADC    | Gaz/fren girişleri            |
| **Telemetri**    | UART       | Pit bilgisayarıyla haberleşme |
| **SD Kart**      | SPI        | Veri kaydı (opsiyonel)        |

---

## Test Senaryoları

- **Araç Başlatma:** IMD veya BMS hata verirse araç açılmaz.  
- **Sürüş Testi:** Pedal → Motor sürücüye doğru tork komutu gider.  
- **Aşırı Sıcaklık:** BMS uyarısı → VCU motoru kapatır.  
- **Veri Kaydı:** SD kartta log dosyası oluşur.  

---

## Kullanım Alanları

- Elektrikli araç kontrol sistemi geliştirme  
- Yarış aracı prototipleri  
- Araç içi güvenlik ve telemetri uygulamaları  

---

##  Gelecek Yol Haritası

- OTA (Over-the-Air) güncelleme  
- Gelişmiş telemetri protokolü  
- Veri analizi için Python araçları  
- Optimize edilmiş enerji yönetim algoritmaları  



 
