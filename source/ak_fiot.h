/* ----------------------------------------------------------------------------------------------- */
/*  Copyright (c) 2018 - 2019 by Axel Kenzo, axelkenzo@mail.ru                                     */
/*                                                                                                 */
/*  Файл ak_fiot.h                                                                                 */
/*  - содержит предварительное описание функций инициализации и настройки контекста                */
/*    защищенного взаимодействия.                                                                  */
/* ----------------------------------------------------------------------------------------------- */
 #ifndef __AK_FIOT_H__
 #define __AK_FIOT_H__

/* ----------------------------------------------------------------------------------------------- */
 #include <ak_mac.h>
 #include <ak_curves.h>
 #include <ak_network.h>

/* ----------------------------------------------------------------------------------------------- */
/*  Группа уникальных ошибок протокола sp fiot */
/*! \brief Ошибка выбора роли участника протокола. */
 #define fiot_error_wrong_role                 (-257)
/*! \brief Ошибка выбора типа интрефейса. */
 #define fiot_error_wrong_interface            (-258)
/*! \brief Передача данных слишком большой длины. */
 #define fiot_error_wrong_send_length          (-259)

/*! \brief Неверное значение, определяющее тип принимаемого фрейма. */
 #define fiot_error_frame_type                 (-258)
/*! \brief Неверное значение, определяющее размер буффера для приема/отправки фреймов. */
 #define fiot_error_frame_size                 (-259)
/*! \brief Неверное значение уникального номера фрейма. */
 #define fiot_error_frame_number               (-260)
/*! \brief Неверное значение типа буффера для приема/передачи данных. */
 #define fiot_error_frame_buffer_type          (-261)
/*! \brief Неверный формат фрейма. */
 #define fiot_error_frame_format               (-262)
/*! \brief Неверно установленный криптографический механизм. */
 #define fiot_error_wrong_mechanism            (-263)
/*! \brief Неверно установленные ограничения для криптографических механизмов. */
 #define fiot_error_wrong_restrictions         (-264)
/*! \brief Неверно заданный набор параметров эллиптической кривой. */
 #define fiot_error_unknown_paramset           (-265)
/*! \brief Неверное значение типа предварительно распределенного ключа. */
 #define fiot_error_wrong_psk_type             (-266)
/*! \brief Использование неопределенного/неверного идентификатора предварительно распределенного ключа */
 #define fiot_error_wrong_psk_identifier_using (-267)
/*! \brief Неверное значение типа используемого генератора случайных чисел. */
 #define fiot_error_wrong_random_generator     (-268)
/*! \brief Ошибка генерации случайных данных. */
 #define fiot_error_bad_random_data            (-269)
/*! \brief Неверно заданный тип алгоритма блочного шифрования */
 #define fiot_error_wrong_cipher_type          (-270)
/*! \brief Неверно заданный тип алгоритма вычисления имитовставки */
 #define fiot_error_wrong_integrity_algorithm  (-271)
/*! \brief Неверно заданное (неожидаемое в данный момент) значение состояния контекста. */
 #define fiot_error_wrong_state                (-272)

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Допустимые роли участников защищенного взаимодействия. */
 typedef enum {
  /*! \brief Роль не определена. */
   undefined_role,
  /*! \brief Участник выполняет роль клиента. */
   client_role,
  /*! \brief Участник выполняет роль сервера. */
   server_role
} role_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Идентификатор буффера, используемого для приема и отправки фреймов. */
 typedef enum {
  /*! \brief Буффер, используемый для приема сообщений. */
   inframe = 0x0,
  /*! \brief Буффер, используемый для отправки сообщений. */
   oframe = 0x1
} frame_buffer_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип фрейма.
    \details Тип определяет способ передачи информации, вкладываемой во фрейм - информация
    передается в зашифрованном или не зашифрованном виде. Константа в перечислении определяет
    значение второго (начиная с младших) бита, см. раздел 7 спецификации протокола.                                                           */
/* ----------------------------------------------------------------------------------------------- */
 typedef enum {
  /*! \brief Фрейм передается в незашифрованном виде. */
   plain_frame = 0x00U,
  /*! \brief Фрейм передается в зашифрованном виде. */
   encrypted_frame = 0x02U
} frame_type_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип данных, информирующий о том, представлены ли данные, или нет. */
 typedef enum {
    not_present = 0xB0,
    is_present = 0xB1
} present_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип данных, информирующий о наличии или отсутствии запроса. */
 typedef enum {
    not_requested = 0xB0,
    is_requested = 0xB1
} request_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип используемых сертификатов открытых ключей. */
 typedef enum {
    plain = 0x10,
    x509 = 0x19,
    cvc = 0x20
 } certificate_format_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Способ выбора запрашиваемого к использованию сертификата. */
 typedef enum {
    any = 0x00,
    number = 0x10,
    issuer = 0x20
} certificate_processed_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип передаваемого сообщения. */
 typedef enum {
    undefined_message = 0x0,
    client_hello = 0x11,
    server_hello = 0x12,
    verify_message = 0x13,
    application_data = 0x14,
    alert_message = 0x15,
    generate_psk = 0x16,
    extension_request_certificate = 0x21,
    extension_certificate = 0x22,
    extension_set_ertificate = 0x23,
    extension_inform_certificate = 0x24,
    extension_request_identifer = 0x25,
    extension_key_echanism = 0x26
} message_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип, определяющий текущий набор используемых криптографических механизмов. */
 typedef enum {
    not_set_mechanism = 0x0000,
    streebog256 = 0x0013,
    streebog512 = 0x0023,
    magmaGOST3413ePSK = 0x2051,
    kuznechikGOST3413ePSK = 0x2052,
    magmaGOST3413iPSK = 0x3101,
    kuznechikGOST3413iPSK = 0x3102,
    hmac256ePSK = 0x2033,
    hmac512ePSK = 0x2043,
    hmac256iPSK = 0x3033,
    hmac512iPSK = 0x3043,
    magmaCTRplusHMAC256 = 0x1131,
    magmaCTRplusGOST3413 = 0x1151,
    kuznechikCTRplusHMAC256 = 0x1132,
    kuznechikCTRplusGOST3413 = 0x1152,
    magmaAEAD = 0x1201,
    kuznechikAEAD = 0x1202,
} crypto_mechanism_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Допустимые алгоритмы блочного шифрования, прил. Б.2.8 */
 typedef enum {
    undefined_cipher = 0x00,
    magma_cipher = 0x01,
    kuznechik_cipher = 0x02,
    null_cipher = 0x03
} block_cipher_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Допустимые алгоритмы вычисления кода целостности, прил. Б.2.8 */
 typedef enum {
  undefined_integrity_function = 0x00,
  streebog256_function = 0x01,
  streebog512_function = 0x02,
  hmacStreebog256_function = 0x03,
  hmacStreebog512_function = 0x04,
  imgost3413_function = 0x05,
} integrity_function_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Допустимые варианты используемых ключей, прил. Б.2.8 */
 typedef enum {
  /*! \brief Ключа не определен или не используется. */
   undefined_key = 0x00,
  /*! \brief Производный ключ. */
   derivative_key = 0x01,
  /*! \brief Симметричный, предварительно распределенный ключ аутентификации. */
   ePSK_key = 0x02,
  /*! \brief Симметричный ключ, выработанный в ходе протокола выработки ключа аутентификации. */
   iPSK_key = 0x03
} key_type_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Используемые наборы параметров эллиптических кривых. */
 typedef enum {
    unknown_paramset = 0x00,
    tc26_gost3410_2012_256_paramsetA = 0x01,
    tc26_gost3410_2012_512_paramsetA = 0x02,
    tc26_gost3410_2012_512_paramsetB = 0x03,
    tc26_gost3410_2012_512_paramsetC = 0x04,
    rfc4357_gost3410_2001_paramsetA = 0x05,
    rfc4357_gost3410_2001_paramsetB = 0x06,
    rfc4357_gost3410_2001_paramsetC = 0x07
} elliptic_curve_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Различные типы длин передаваемых фреймов. */
 typedef enum {
   small_frame = 0x00,
   long_frame = 0x01
} crypto_frame_length_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Допустимые классы средств СКЗИ. */
 typedef enum {
   base_class  = 0x05,
   KC_class = 0x06,
   KA_class = 0x07
} crypto_class_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Режимы использования криптографических механизмов (определяют технические характеристики
    протокола sp fiot).
    \details Указанные значения зависят от максимальной длины передаваемых фреймов, используемого
    блочного шифра, а также класса средства защиты. Значения определяются следующим образом:
    - нулевой (младший) бит (0 - сообщения не превосходят 1500 октетов, 1 - иначе ),
    - первый бит - всегда ноль (резерв),
    - третий/четвертый биты: класс средства (01 - не классифицируемое средство, 10 - класс КС3 и ниже,
      11 - классы КВ и КА)
    - пятый/шестой биты: используемый блочный шифр (01 - Магма, 10 - Кузнечик).                    */
/* ----------------------------------------------------------------------------------------------- */
 typedef enum {
   undefinedKeyMechanism = 0x00,
   baseKeyMechanismMagma = ( small_frame | base_class | ( magma_cipher << 4 )),
   baseKeyMechanismKuznechik = ( small_frame | base_class | ( kuznechik_cipher << 4 )),
   shortKCMechanismMagma = ( small_frame | KC_class | ( magma_cipher << 4 )),
   shortKCMechanismKuznechik = ( small_frame | KC_class | ( kuznechik_cipher << 4 )),
   longKCMechanismMagma = ( long_frame | KC_class | ( magma_cipher << 4 )),
   longKCMechanismKuznechik = ( long_frame | KC_class | ( kuznechik_cipher << 4 )),
   shortKAMechanismMagma = ( small_frame | KA_class | ( magma_cipher << 4 )),
   shortKAMechanismKuznechik = ( small_frame | KA_class | ( kuznechik_cipher << 4 )),
   longKAMechanismMagma =( long_frame | KA_class | ( magma_cipher << 4 )),
   longKAMechanismKuznechik = ( long_frame | KA_class | ( kuznechik_cipher << 4 ))
} key_mechanism_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Набор ограничений (параметров) для защищенного взаимодействия, см. прил. Г. */
 typedef struct crypto_restriction {
  /*! \brief Максимальная длина сериализованного представления структуры Frame. */
   unsigned int maxFrameLength;
  /*! \brief Максимальное количество фреймов, зашифровываемых на одном ключе. */
   unsigned int maxFrameCount;
  /*! \brief Максимальное количество пар производных ключей шифрования и имитовставки. */
   unsigned int maxFrameKeysCount;
  /*! \brief Максимальное количество преобразований ключевой информации в рамках одного сеанса связи. */
   unsigned int maxApplicationSecretCount;
} *ak_crypto_restriction;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура, содержащая параметры политики поведеня сервера при сетевом взаимодействии. */
 typedef struct policy {
  /*! \brief Криптографические механизмы, используеумые для обмена зашифрованной информацией. */
   crypto_mechanism_t mechanism;
  /*! \brief Набор ограничений, накладываемых на криптографические алгоритмы.
      \details Данное значение зависит от класса средства защиты, длины передаваемых фреймов
      и используемых криптографических алгоритмов. Значение поля `restrictions`
      устанавливается функцией ak_fiot_context_set_secondary_crypto_mechanism()
      в процессе выполнения проткола выработки общих ключей. */
   struct crypto_restriction restrictions;
} *ak_policy;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Тип ошибки, возвращаемой в ходе выполнения протокола sp fiot. */
 typedef enum {
    unknownError = 0x1000,
    unsupportedCryptoMechanism = 0x1001,
    wrongExternalPreSharedKey = 0x1002,
    wrongInternalPreSharedKey = 0x1003,
    wrongIntegrityCode = 0x1004,
    lostIntegrityCode = 0x1005,
    wrongCertificateProcessed = 0x100a,
    wrongCertificateNumber = 0x100b,
    expiredCertificate = 0x100c,
    unsupportedCertificateNumber = 0x100d,
    notValidCertificateNumber = 0x100e,
    wrongCertificateApplication = 0x100f,
    wrongCertificateIssuer = 0x1010,
    unsupportedCertificateIssuer = 0x1011,
    unsupportedCertificateFormat = 0x1012,
    wrongCertificateIntegrityCode = 0x1013,
    usupportedKeyMechanism = 0x1020,
    unsupportedEllipticCurveID = 0x1031,
    wrongEllipticCurvePoint = 0x1032,
    wrongInternalPSKIdentifier = 0x1040
} alert_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Возможные состояния контекста защищенного взаимодействия для клиента и сервера
    в ходе выполнения протокола выработки общих ключей.

    \details Константы `rts` (ready to send) описывают состояние готовности к отправке
    сообщения. Константы `wait` описывают состояние готовности к приему сообщения.
    В каждом состоянии клиент и сервер могут выполнить только одно действие по приему
    или передаче сообщений.                                                                        */
/* ----------------------------------------------------------------------------------------------- */
 typedef enum {
 /*! \brief Неопределенное состояние, устанавливается при создании контекста. */
   undefined_state,
 /* последовательность состояний клиента */
 /*! \brief Клиент готов отправить сообщение ClientHello */
   rts_client_hello,
 /*! \brief Клиент готов отправить расширение ClientExtension в ходе первого шага протокола */
   rts_client_extension,
 /*! \brief Клиент готов к приему от сервера сообщения ServerHello */
   wait_server_hello,
 /*! \brief Клиент готов к приему от сервера расширений ServerExtension */
   wait_server_extension,
 /*! \brief Клиент готов к приему от сервера сообщения ServerVerify */
   wait_server_verify,
 /*! \brief Клиент готов отправить расширение ClientExtension в ходе первого шага протокола */
   rts_client_extension2,
 /*! \brief Клиент готов отправить сообщение ClientVerify */
   rts_client_verify,
 /*! \brief Клиент готов к приему от сервера прикладных данных.
     \details Признак завершения клиентом протокола выработки общих ключей. */
   wait_server_application_data,

 /* последовательность состояний сервера */
 /*! \brief Сервер готов к приему от клиента сообщения ClientHello */
   wait_client_hello,
 /*! \brief Сервер готов к приему от клиента расширений ClientExtensions */
   wait_client_extension,
 /*! \brief Сервер готов к отправке сообщения ServerHello */
   rts_server_hello,
 /*! \brief Сервер готов к отправке расширений ServerExtension */
   rts_server_extension,
 /*! \brief Сервер готов к отправке сообщения ServerVerify */
   rts_server_verify,
 /*! \brief Сервер готов к приему от клиента расширений ClientExtension */
   wait_client_extension2,
 /*! \brief Сервер готов к приему от клиента сообщения ClientVerify */
   wait_client_verify,
 /*! \brief Сервер готов к приему от клиента прикладных данных
     \details Признак завершения сервером протокола выработки общих ключей. */
   wait_client_application_data
} context_state_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Перечисление, определяющее возможный тип сетевого интерфейса. */
 typedef enum {
  /*! \brief Сетевой интерфейс не определен. */
   undefined_interface = ak_network_undefined_socket,
  /*! \brief Сетевой интерфейс, через который передаются зашифрованные данные. */
   encryption_interface = 0,
  /*! \brief Сетевой интерфейс, через который передаются открытые данные. */
   plain_interface = 1
 } interface_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Структура, определяющая множество счетчиков, из которых формируется номер фрейма. */
 typedef struct counter {
  /*! \brief Значение счетчика,
      определяющего количество фреймов, зашифрованных на одном ключе. */
   size_t l;
  /*! \brief Значение счетчика,
      определяющего количество преобразований производный ключей шифрования и имитозащиты. */
   size_t m;
  /*! \brief Значение счетчика,
      определяющего количество преобразований общей ключевой информации. */
   size_t n;
} *ak_counter;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Перечисление, определяющее возможные направления передачи информации
    в рамках одного интерфейса. */
 typedef enum {
  /*! \brief Входящая информация. */
   direct_in,
  /*! \brief Исходящая информация. */
   direct_out
} direct_t;

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Минимальный уровень аудита сетевых приложений */
 #define fiot_log_minimal                         ( ak_log_maximum + 1 )
/*! \brief Стандартный уровень аудита сетевых приложений */
 #define fiot_log_standard                        ( ak_log_maximum + 2 )
/*! \brief Параноидальный уровень аудита сетевых приложений */
 #define fiot_log_maximum                         ( ak_log_maximum + 3 )

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Минимальный размер фрейма. */
 #define fiot_min_frame_size        (256)
/*! \brief Размер фрейма по-умолчанию. */
 #define fiot_frame_size           (1472)
/*! \brief Максимальный размер фрейма. */
 #define fiot_max_frame_size      (16356)
/*! \brief Смещение зашифровываемых данных от начала фрейма (для базового заголовка). */
 #define fiot_frame_header_offset     (8)
/*! \brief Смещение собственно сообщения от начала фрейма (для базового заголовка). */
 #define fiot_frame_message_offset   (11)

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Контекст защищенного соединения протокола sp fiot.
    \details Контекст представляет собой фильтр, позволяющий инкапсулировать передаваемую по
    каналам связи информацию.

*/
 typedef struct fiot {
  /*! \brief Буфер, используемый для формирования исходящих фреймов. */
  /*! \details Размер буффера определяет максимально возможный размер передаваемых в канал
      связи данных - фреймов, с учетом размера заголовка, имитовставки и служебных полей.
      Размер буффера может изменяться в ходе выполнения защищенного взаимодействия. */
   struct buffer oframe;

  /*! \brief Буфер, используемый для разбора входящих фреймов.
      \details Размер буффера может изменяться в фиксированных пределах,
      определяемых константами \ref FIOT_MIN_FRAME_SIZE и \ref FIOT_MAX_FRAME_SIZE. Изменение
      контролируется размерами входящих сообщений. */
   struct buffer inframe;

  /*! \brief Смещение зашифровываемых данных от начала фрейма (длина расширяемого заголовка).
      \details Для стандартного заголовка равна 8 октетам. Для расширяемого заголовка может принимать
      любое значение от восьми до 64-х. */
   size_t header_offset;

  /*! \brief Дополнительные данные, помещаемые в заголовок фрейма.
      \details Данные передаются по каналам связи в незашифрованном виде. */
   struct buffer header_data;

  /*! \brief Роль участника взаимодействия */
   role_t role;
  /*! \brief Текущее состояние контекста. */
   context_state_t state;
  /*! \brief Используемый в текущий момент набор криптографических механизмов. */
   crypto_mechanism_t mechanism;
  /*! \brief Политика сетевого взаимодействия. */
   struct policy policy;
  /*! \brief Набор счетчиков для входящей информации. */
   struct counter in_counter;
  /*! \brief Набор счетчиков для исходящей информации. */
   struct counter out_counter;
  /*! \brief Дескриптор чтения/записи для интерфейса, отправляющего/получающего зашифрованные данные . */
   ak_socket iface_enc;
   /*! \brief Дескриптор чтения/записи для интерфейса, отправляющего/получающего открытые данные. */
   ak_socket iface_plain;
  /*! \brief Указатель на функцию записи данных в канал связи. */
   fiot_function_socket_write *write;
  /*! \brief Указатель на функцию получения данных из канала связи. */
   fiot_function_socket_read *read;
  /*! \brief Значение таймаута при ожидании входящих пакетов (в секундах) */
   time_t timeout;

  /*! \brief Идентификатор сервера, должен быть определен всегда. */
   struct buffer server_id;
  /*! \brief Идентификатор клиента.
      \details Перед началом выполнения протокола может быть не определен. Вместе с тем,
      значение может быть определено в ходе выполнения протокола, либо задано пользователем. */
   struct buffer client_id;

  /*! \brief Идентификатор используемой эллиптической кривой. */
   elliptic_curve_t curve_id;
  /*! \brief Используемая эллиптическая кривая, на которой происходит выполнение протокола
      выработки общих ключей. */
   struct wcurve *curve;
  /*! \brief Массив для хранения случайных секретных данных. */
   ak_uint64 secret[ak_mpzn512_size];
  /*! \brief Временная точка эллиптической кривой, используемая в ходе выполнения протокола
      выработки общих ключей. */
   struct wpoint point;

  /*! \brief Генератор для масок, случайного дополнения и т.п. */
   struct random plain_rnd;
  /*! \brief Генератор для выработки криптографически опасной информации. */
   struct random crypto_rnd;

  /*! \brief Контекст бесключевой функции хеширования Стрибог-512.
      \details Структура используется для вычисления хэш-кода от всех сообщений,
      передаваемых в ходе выполнения протокола выработки общих ключей. */
   struct mac comp;

  /* ak_skey secret */
  /*! \brief Ключевая информация, используемая для передачи зашифрованных сообщений от
      сервера к клиенту. В тексте рекомендаций обозначается SHTS и SATS. */
   ak_uint8 server_ts[64];
  /*! \brief Ключевая информация, используемая для передачи зашифрованных сообщений от
      клиента к серверу. В тексте рекомендаций обозначается CHTS и CATS. */
   ak_uint8 client_ts[64];

  /*! \brief Ключ шифрования информации, передаваемой от клиента к серверу */
   struct bckey ecfk;
  /*! \brief Ключ шифрования информации, передаваемой от сервера к клиенту */
   struct bckey esfk;
  /*! \brief Ключ имитозащиты информации, передаваемой от клиента к серверу */
   struct mac icfk;
  /*! \brief Ключ имитозащиты информации, передаваемой от сервера к клиенту */
   struct mac isfk;

  /*! \brief Идентификатор симметричного ключа аутентификации. */
   struct buffer epsk_id;
  /*! \brief Симметричный, предварительно распределенный ключ аутентификации.
      \details В качестве такого ключа может выступать либо предварительно
      распределенный ключ аутентификации `ePSK`, либо выработанный в ходе предыдущего
      сеанса взаимодействия ключ `iPSK`.

      Кроме того, данный контекст используется для некриптографического контроля
      целостности при аутентификации с использованием асимметричных ключей
      (ключей электронной подписи). */
    struct mac epsk;
  /*! \brief Тип симмеричного ключа аутентификации.
      \details Данная константа инициализируется при установке идентификатора симметричного
      ключа аутентификации и передается в составе сообщения `ClientHello`. */
   key_type_t epsk_type;

} *ak_fiot;

/* ----------------------------------------------------------------------------------------------- */
/** \addtogroup fiot_functions Функции создания и настройки параметров контекста защищенного взаимодействия
 *  \details Данная группа функций позволяет создавать и настраивать контексты защищенного взаимодействия
 *   двух произвольных процессов с помощью протокола [sp fiot](https://tc26.ru/standarts/metodicheskie-rekomendatsii/mr-26-4-003-2018-kriptograficheskie-mekhanizmy-zashchishchennogo-vzaimodeystviya-kontrolnykh-i-izmeritelnykh-ustroystv.html).
 * @{*/
/*! \brief Инициализация контекста протокола sp fiot. */
 int ak_fiot_context_create( ak_fiot );
/*! \brief Уничтожение содержимого контекста протокола sp fiot. */
 int ak_fiot_context_destroy( ak_fiot );
/*! \brief Уничтожение содержимого контекста протокола sp fiot и освобождение памяти. */
 ak_pointer ak_fiot_context_delete( ak_pointer );
/*! \brief Изменение максимально допустимого размера фрейма протокола sp fiot. */
 int ak_fiot_context_set_frame_size( ak_fiot , frame_buffer_t , size_t );
/*! \brief Получение текущего значения размера одного фрейма протокола sp fiot. */
 size_t ak_fiot_context_get_frame_size( ak_fiot , frame_buffer_t );
/*! \brief Установка роли участника защищенного соединения. */
 int ak_fiot_context_set_role( ak_fiot , const role_t );
/*! \brief Получение роли участника защищенного взаимодействия. */
 role_t ak_fiot_context_get_role( ak_fiot );
/*! \brief Получение текущего статуса контекста защищенного взаимодействия. */
 context_state_t ak_fiot_context_get_state( ak_fiot );

/*! \brief Установка идентификатора участника защищенного взаимодействия. */
 int ak_fiot_context_set_user_identifier( ak_fiot , role_t , void *, const size_t );
/*! \brief Получение идентификатора участника защищенного взаимодействия. */
 ssize_t ak_fiot_context_get_user_identifier( ak_fiot , role_t , void *, const size_t );
/*! \brief Установка идентификатора используемой эллиптической кривой. */
 int ak_fiot_context_set_curve( ak_fiot , elliptic_curve_t );
/*! \brief Получение текущего идентификатора эллиптической кривой. */
 elliptic_curve_t ak_fiot_context_get_curve( ak_fiot );

/*! \brief Присвоение заданному интерфейсу контекста открытого сокета. */
 int ak_fiot_context_set_interface_descriptor( ak_fiot , interface_t, ak_socket );
/*! \brief Получение дескриптора сокета для заданного интерфейса контекста защищенного взаимодействия. */
 ak_socket ak_fiot_context_get_interface_descriptor( ak_fiot , interface_t );
/*! \brief Установка идентификатора симметричного ключа аутентификации. */
 int ak_fiot_context_set_psk_identifier( ak_fiot , key_type_t , void * , const size_t );
/*! \brief Функия присваивает значение предварительно распределенному ключу. */
 int ak_fiot_context_set_psk_key( ak_fiot );
/*! \brief Установка первичного набора криптографических механизмов. */
 int ak_fiot_context_set_initial_crypto_mechanism( ak_fiot , crypto_mechanism_t );
/*! \brief Установка набора криптографических механизмов, используемых для обмена зашифрованной информацией. */
 int ak_fiot_context_set_secondary_crypto_mechanism( ak_fiot , crypto_mechanism_t );
/*! \brief Установка политики поведения сервера. */
 int ak_fiot_context_set_server_policy( ak_fiot , crypto_mechanism_t );
/** @} */

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Функция возвращает идентификатор блочного шифра по заданному набору
    криптографических механизмов. */
 block_cipher_t ak_fiot_get_block_cipher( const crypto_mechanism_t );
/*! \brief Функция возвращает идентификатор алгоритма выработки имитовставки по заданному набору
    криптографических механизмов. */
 integrity_function_t ak_fiot_get_integrity_function( const crypto_mechanism_t );
/*! \brief Функция возвращает тип ключа по заданному набору криптографических механизмов. */
 key_type_t ak_fiot_get_key_type( const crypto_mechanism_t );
/*! \brief Функция возвращает размер (в байтах) x-координаты точки эллиптической кривой. */
 size_t ak_fiot_get_point_size( const elliptic_curve_t );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Формирование ключевой информации CHTS. */
 int ak_fiot_context_create_chts_keys( ak_fiot );
/*! \brief Формирование ключевой информации CHTS. */
 int ak_fiot_context_create_shts_keys( ak_fiot );
/*! \brief Функция создает первичное состояние общей ключевой информации. */
 int ak_fiot_context_create_ats_keys( ak_fiot );
/*! \brief Функция выработки следующего состояния общей ключевой информации. */
 int ak_fiot_context_create_next_ats_keys( ak_fiot , direct_t );
/*! \brief Функция выработки производных ключей шифрования и имитозащиты. */
 int ak_fiot_context_create_next_derivative_keys( ak_fiot , direct_t );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Выполнение протокола выработки общих ключей. */
 int ak_fiot_context_keys_generation_protocol( ak_fiot );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Отправка сообщения прикладного уровня. */
 int ak_fiot_context_write_application_data( ak_fiot , ak_pointer , size_t );
/*! \brief Отправка сообщения об ошибке. */
 int ak_fiot_context_write_alert_message( ak_fiot, alert_t , char * , size_t );
/*! \brief Формирование сообщения транспортного протокола и отправка его в канал связи. */
 int ak_fiot_context_write_frame( ak_fiot , ak_pointer , size_t , frame_type_t , message_t );
/*! \brief Получение данных из канала связи в течение заданного интервала времени. */
 ssize_t ak_fiot_context_read_ptr_timeout( ak_fiot , interface_t , ak_pointer , size_t );
/*! \brief Получение фрейма из канала связи. */
 ak_uint8 *ak_fiot_context_read_frame( ak_fiot , size_t *, message_t * );
/*! \brief Получение данных из канала связи и преобразование их к сериализованному представлению фрейма. */
 ak_uint8 *ak_fiot_context_read_frame_ptr( ak_fiot , size_t * , size_t * , frame_type_t * );

/* ----------------------------------------------------------------------------------------------- */
/*! \brief Вывод содержимого фрейма с использованием системы аудита. */
 int ak_fiot_context_log_frame( ak_uint8 * , size_t , const char * );

#endif
/* ----------------------------------------------------------------------------------------------- */
/*                                                                                          fiot.h */
/* ----------------------------------------------------------------------------------------------- */
