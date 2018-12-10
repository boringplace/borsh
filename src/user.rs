use std::time::Instant;

use verificator::method::AuthMethod;

/**
 * Structure representing registrant.
 */
pub struct User {
    name: String,
    active: bool,
    confirmed: bool,
    expiration: Instant,
    amethod: AuthMethod,
}

impl User {
    /**
     * Create the new user data structure with some defaults.
     */
    pub fn new(username: String) -> Self {
        let usr : User = User { name: username,
            active: false,
            confirmed: false,
            expiration: Instant::now(),
            amethod: AuthMethod::Email,
        };
        return usr;
    }

    /**
     * Change account name.
     */
    pub fn update_name(&mut self, username: String) {
        self.name = username;
    }

    /**
     * Set if account is active or blocked.
     */
    pub fn update_active(&mut self, is_active: bool) {
        self.active = is_active;
    }

    /**
     * Set if account is confirmed or not.
     */
    pub fn update_confirmation(&mut self, is_confirmed: bool) {
        self.confirmed = is_confirmed;
    }

    /**
     * Set the account expiration date.
     */
    pub fn update_expiration(&mut self, timestamp: Instant) {
        self.expiration = timestamp;
    }

    /**
     * Set authentication method for the user.
     */
    pub fn update_auth_method(&mut self, method: AuthMethod) {
        self.amethod = method;
    }

    /**
     * Get the user's name.
     */
    pub fn name(&self) -> &String {
        return &self.name;
    }

    /**
     * Check if account is not blocked.
     */
    pub fn is_active(&self) -> &bool {
        return &self.active;
    }

    /**
     * Check if account is confirmed by the user.
     */
    pub fn is_confirmed(&self) -> &bool {
        return &self.confirmed;
    }

    /**
     * Get the account expiration date.
     */
    pub fn expiration(&self) -> &Instant {
        return &self.expiration;
    }

    /**
     * The user account is expired if expiration date/time is greater
     * than now.
     */
    pub fn is_expired(&self) -> bool {
        return self.expiration.gt(&Instant::now());
    }


    /**
     * Get the authentication method set for the user.
     */
    pub fn auth_method(&self) -> &AuthMethod {
        return &self.amethod;
    }
}

