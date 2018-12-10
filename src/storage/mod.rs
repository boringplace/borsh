pub mod storage_type;

/* Various supported backends */
mod sqlite;

use crate::user::User;
use crate::settings::Settings;

use self::storage_type::StorageType;
use self::sqlite::SQLiteStorage;

/**
 * Database connection context.
 */
//#[derive(Copy, Clone)]
pub struct StorageSettings {
    path: Option<String>,
    login: Option<String>,
    password: Option<String>,
    addr: Option<String>,
    stype: StorageType,
}

impl StorageSettings {
    /**
     * Create a storage settings for SQLite3 database which only
     * requires path to the file.
     */
    pub fn new_local(storage_type: StorageType, path: &str) -> Self {
        let sset : StorageSettings = StorageSettings {
            path: Some(String::from(path)),
            login: None,
            password: None,
            addr: None,
            stype: storage_type,
        };
        return sset;
    }

    /**
     * Create a storage settings for remote database.
     */
    pub fn new_remote(storage_type: StorageType,
        ulogin: &str,
        upassword: &str,
        uaddr: &str) -> Self {
        let sset : StorageSettings = StorageSettings {
            path: None,
            login: Some(String::from(ulogin)),
            password: Some(String::from(upassword)),
            addr: Some(String::from(uaddr)),
            stype: storage_type,
        };
        return sset;
    }

    pub fn get_storage_type(&self) -> StorageType {
        return self.stype;
    }
}

pub trait StorageBackend {
    /**
     * Change user settings.
     */
    fn update_user(&self, user: &User);

    /**
     * Check if the specified user is present in the database.
     */
    fn user_present(&self, user: &User) -> bool;
}

impl StorageBackend for SQLiteStorage {
    fn update_user(&self, user: &User) {
        return self.update(user);
    }

    fn user_present(&self, user: &User) -> bool {
        return self.user_present(user);
    }
}

pub fn get(settings: &StorageSettings) -> Box<StorageBackend> {
    match settings.get_storage_type() {
        StorageType::SQLite => Box::new(SQLiteStorage::new(&"/var/borsh/borsh.sqlite3".to_string())),
    }
}

