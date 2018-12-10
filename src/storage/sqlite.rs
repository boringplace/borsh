extern crate rusqlite;

use self::rusqlite::types::ToSql;
use self::rusqlite::{ Connection, OpenFlags, NO_PARAMS };

use crate::user::User;

pub struct SQLiteStorage {
    path: String,
    connection: Connection,
}

impl SQLiteStorage {
    /**
     * Open the connection to the database and perform the necessary
     * checks. Or panic.
     */
    pub fn new(dst: &String) -> Self {
        let connection = Connection::open_with_flags(dst,
            OpenFlags::SQLITE_OPEN_READ_WRITE | OpenFlags::SQLITE_OPEN_CREATE).unwrap();
        let storage : SQLiteStorage = SQLiteStorage { path: dst.to_string(),
            connection: connection };

        /* Initialize the database if necessary */
        if !SQLiteStorage::check_initialized(&storage.connection) {
            SQLiteStorage::init_db(&storage.connection);
        }

        return storage;
    }

    /**
     * Check if the database has the necessary structures.
     */
    fn check_initialized(connection: &Connection) -> bool {
        //connection.execute("PRAGMA schema_version");
        return false;
    }

    /**
     * Try to initialize the database if it is not already initialized.
     */
    fn init_db(connection: &Connection) {
        connection.execute(r#"CREATE TABLE user (id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            active TEXT NOT NULL,
            expiration TEXT NOT NULL,
            amethod TEXT NOT NULL)"#, NO_PARAMS);
        connection.execute(r#"PRAGMA schema_version = 2;"#, NO_PARAMS);
    }

    /**
     * Change user properties.
     */
    pub fn update(&self, user: &User) {
        self.connection.execute(r#"INSERT INTO user;"#, NO_PARAMS);
    }

    /**
     * Check if the specified username is present in the database.
     */
    pub fn user_present(&self, user: &User) -> bool {
        self.connection.execute(r#"SELECT * FROM user;"#, NO_PARAMS);
        return false;
    }
}

