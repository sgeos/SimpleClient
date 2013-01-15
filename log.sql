CREATE TABLE IF NOT EXISTS user_list
(
  id      INTEGER,
  user    VARCHAR(32),
  time    DATE,
  PRIMARY KEY ( user )
);

CREATE TABLE IF NOT EXISTS message_log
(
  id      INTEGER,
  user    VARCHAR(32),
  message VARCHAR(256),
  time    DATE,
  PRIMARY KEY ( id )
);

-- Login New User
-- INSERT INTO user_list ( id, user, time ) SELECT COALESCE ( MAX ( id ) + 1, 1 ), 'User_' || COALESCE ( MAX ( id ) + 1, 1 ), DATETIME ( 'NOW' ) FROM user_list;

-- Login Existing User
-- INSERT OR REPLACE INTO user_list ( id, user, time )
--   VALUES (
--     COALESCE ( (SELECT id FROM user_list WHERE user='MyUserName'), (SELECT MAX ( id ) + 1 FROM user_list), 1 ),
--     'MyUserName',
--     DATETIME ( 'NOW' )
--   );

-- New Message
-- INSERT INTO message_log ( id, user, message, time ) SELECT COALESCE ( MAX ( id ) + 1, 1 ), 'MyUserName', 'This is my message.', DATETIME ( 'NOW' ) FROM message_log;

-- Message Log
-- SELECT * FROM message_log ORDER BY time DESC LIMIT 50;

