extern crate regex;

use std::io::{ Error, ErrorKind };
use self::regex::Regex;

/**
 * List of supported verification methods.
 */
#[derive(Copy, Clone, PartialEq, Eq, Hash)]
pub enum AuthMethod {
    Email,
    SMS,
}

impl AuthMethod {
    /**
     * Get the authentication method name out of provided string. The
     * function is expected to take an ASCII string and will return
     * error if the provided string is not ASCII.
     */
    pub fn decode_method(method_name: String) -> Result<AuthMethod, Error> {
        if !method_name.is_ascii() {
            return Err(Error::new(ErrorKind::InvalidInput,
                "The provided authentication method name is not in ASCII format."));
        }

        lazy_static! {
            static ref re_sms : Regex   = Regex::new(r#"^[Ss][Mm][Ss]$"#).unwrap();
            static ref re_email : Regex = Regex::new(r#"^[Ee][-]?[Mm][Aa][Ii][Ll]$"#).unwrap();
        }

        let name : &str = &method_name.to_ascii_lowercase();

        if re_sms.is_match(name) {
            return Ok(AuthMethod::SMS);
        }
        if re_email.is_match(name) {
            return Ok(AuthMethod::Email);
        }

        return Err(Error::new(ErrorKind::InvalidData,
            "The provided authentication method name does not match any available methods."));
    }
}

