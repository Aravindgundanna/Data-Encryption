//
// X509Certificate.h
//
// $Id: //poco/1.7/Crypto/include/Poco/Crypto/X509Certificate.h#2 $
//
// Library: Crypto
// Package: Certificate
// Module:  X509Certificate
//
// Definition of the X509Certificate class.
//
// Copyright (c) 2006-2009, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Crypto_X509Certificate_INCLUDED
#define Crypto_X509Certificate_INCLUDED


#include "Poco/Crypto/Crypto.h"
#include "Poco/Crypto/OpenSSLInitializer.h"
#include "Poco/DateTime.h"
#include "Poco/SharedPtr.h"
#include <set>
#include <istream>
#include <openssl/ssl.h>


namespace Poco {
namespace Crypto {


class Crypto_API X509Certificate
	/// This class represents a X509 Certificate.
{
public:
	enum NID
		/// Name identifier for extracting information from
		/// a certificate subject's or issuer's distinguished name.
	{
		NID_COMMON_NAME = 13,
		NID_COUNTRY = 14,
		NID_LOCALITY_NAME = 15,
		NID_STATE_OR_PROVINCE = 16,
		NID_ORGANIZATION_NAME = 17,
		NID_ORGANIZATION_UNIT_NAME = 18	
	};
	
	explicit X509Certificate(std::istream& istr);
		/// Creates the X509Certificate object by reading
		/// a certificate in PEM format from a stream.

	explicit X509Certificate(const std::string& path);
		/// Creates the X509Certificate object by reading
		/// a certificate in PEM format from a file.

	explicit X509Certificate(X509* pCert);
		/// Creates the X509Certificate from an existing
		/// OpenSSL certificate. Ownership is taken of 
		/// the certificate.

	X509Certificate(X509* pCert, bool shared);
		/// Creates the X509Certificate from an existing
		/// OpenSSL certificate. Ownership is taken of 
		/// the certificate. If shared is true, the 
		/// certificate's reference count is incremented.

	X509Certificate(const X509Certificate& cert);
		/// Creates the certificate by copying another one.

	X509Certificate& operator = (const X509Certificate& cert);
		/// Assigns a certificate.
 
	void swap(X509Certificate& cert);
		/// Exchanges the certificate with another one.

	~X509Certificate();
		/// Destroys the X509Certificate.

	const std::string& issuerName() const;
		/// Returns the certificate issuer's distinguished name. 
		
	std::string issuerName(NID nid) const;
		/// Extracts the information specified by the given
		/// NID (name identifier) from the certificate issuer's
		/// distinguished name.
		
	const std::string& subjectName() const;
		/// Returns the certificate subject's distinguished name.

	std::string subjectName(NID nid) const;
		/// Extracts the information specified by the given
		/// NID (name identifier) from the certificate subject's
		/// distinguished name.
		
	std::string commonName() const;
		/// Returns the common name stored in the certificate
		/// subject's distinguished name.
		
	void extractNames(std::string& commonName, std::set<std::string>& domainNames) const;
		/// Extracts the common name and the alias domain names from the
		/// certificate.
		
	Poco::DateTime validFrom() const;
		/// Returns the date and time the certificate is valid from.
		
	Poco::DateTime expiresOn() const;
		/// Returns the date and time the certificate expires.
		
	void save(std::ostream& stream) const;
		/// Writes the certificate to the given stream.
		/// The certificate is written in PEM format.

	void save(const std::string& path) const;
		/// Writes the certificate to the file given by path.
		/// The certificate is written in PEM format.
		
	bool issuedBy(const X509Certificate& issuerCertificate) const;
		/// Checks whether the certificate has been issued by
		/// the issuer given by issuerCertificate. This can be
		/// used to validate a certificate chain.
		///
		/// Verifies if the certificate has been signed with the
		/// issuer's private key, using the public key from the issuer
		/// certificate.
		///
		/// Returns true if verification against the issuer certificate
		/// was successfull, false otherwise.

	bool equals(const X509Certificate& otherCertificate) const;
		/// Checks whether the certificate is equal to
		/// the other certificate, by comparing the hashes
		/// of both certificates.
		///
		/// Returns true if both certificates are identical,
		/// otherwise false.

	const X509* certificate() const;
		/// Returns the underlying OpenSSL certificate.

protected:
	void load(std::istream& stream);
		/// Loads the certificate from the given stream. The
		/// certificate must be in PEM format.
		
	void load(const std::string& path);
		/// Loads the certificate from the given file. The
		/// certificate must be in PEM format.

	void init();
		/// Extracts issuer and subject name from the certificate.
	
private:
	enum
	{
		NAME_BUFFER_SIZE = 256
	};
	
	std::string _issuerName;
	std::string _subjectName;
	X509*       _pCert;
	OpenSSLInitializer _openSSLInitializer;
};


//
// inlines
//
inline const std::string& X509Certificate::issuerName() const
{
	return _issuerName;
}


inline const std::string& X509Certificate::subjectName() const
{
	return _subjectName;
}


inline const X509* X509Certificate::certificate() const
{
	return _pCert;
}


} } // namespace Poco::Crypto


#endif // Crypto_X509Certificate_INCLUDED
