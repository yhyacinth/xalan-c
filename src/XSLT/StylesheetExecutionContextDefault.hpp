/*
 * The Apache Software License, Version 1.1
 *
 *
 * Copyright (c) 1999 The Apache Software Foundation.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:  
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xalan" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written 
 *    permission, please contact apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com.  For more
 * information on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 *
 * @author <a href="mailto:david_n_bertoni@lotus.com">David N. Bertoni</a>
 */
#if !defined(STYLESHEETEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680)
#define STYLESHEETEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680



// Base class include file.
#include "Stylesheet.hpp"
#include "StylesheetExecutionContext.hpp"



#include <ctime>
#include <deque>
#include <memory>
#include <set>
#include <vector>



#include <XPath/XPathExecutionContextDefault.hpp>



#include <XSLT/VariablesStack.hpp>


class Stylesheet;
class TextOutputStream;
class XPathProcessor;
class XPathSupport;
class XObjectFactory;
class XSLTEngineImpl;



//
// An class which provides support for executing stylesheets.
//
class XALAN_XSLT_EXPORT StylesheetExecutionContextDefault : public StylesheetExecutionContext
{
public:

	StylesheetExecutionContextDefault(
			XSLTEngineImpl&			xsltProcessor,
			XPathEnvSupport&		theXPathEnvSupport,
			XPathSupport&			theXPathSupport,
			XObjectFactory&			theXObjectFactory,
			XalanNode*				theCurrentNode = 0,
			const NodeRefListBase*	theContextNodeList = 0,
			const PrefixResolver*	thePrefixResolver = 0);

	virtual
	~StylesheetExecutionContextDefault();

	// These interfaces are inherited from StylesheetExecutionContext...

	virtual void
	reset();

	virtual bool
	getQuietConflictWarnings() const;

	virtual XalanNode*
	getRootDocument() const;

	virtual void
	setRootDocument(XalanNode*	theDocument);

	virtual XalanDocument*
	createDocument() const;

	virtual void
	setStylesheetRoot(const StylesheetRoot*		theStylesheet);

	virtual void
	resetCurrentState(
			XalanNode*	sourceTree,
			XalanNode*	xmlNode);

	virtual bool
	doDiagnosticsOutput() const;

	virtual void
	diag(const XalanDOMString&	theString);

	virtual void
	pushTime(const void*	theKey);

	virtual void
	displayDuration(
			const XalanDOMString&	theMessage,
			const void*				theKey);

	virtual const AttributeList&
	getPendingAttributes() const;

	virtual XalanDOMString
	getPendingElementName() const;

	virtual void
	setPendingAttributes(const AttributeList&	pendingAttributes);

	virtual void
	replacePendingAttribute(
			const XalanDOMChar*		theName,
			const XalanDOMChar*		theNewType,
			const XalanDOMChar*		theNewValue);

	virtual void
	setPendingElementName(const XalanDOMString&		elementName);

	virtual void
	addResultAttribute(
			const XalanDOMString&	aname,
			const XalanDOMString&	value);

	virtual void
	copyNamespaceAttributes(
			const XalanNode&	src,
			bool				srcIsStylesheetTree);

	virtual XalanDOMString
	getResultPrefixForNamespace(const XalanDOMString&	theNamespace) const;

	virtual XalanDOMString
	getResultNamespaceForPrefix(const XalanDOMString&	thePrefix) const;

	virtual XalanDOMString
	getUniqueNameSpaceValue() const;

	virtual FormatterListener*
	getFormatterListener() const;

	virtual void
	setFormatterListener(FormatterListener*		flistener);

	virtual bool
	getHasPendingStartDocument() const;

	virtual void
	setHasPendingStartDocument(bool	b);

	virtual bool
	getMustFlushPendingStartDocument() const;

	virtual void
	setMustFlushPendingStartDocument(bool	b);

	virtual int
	getIndent() const;

	// $$$ ToDo: Get rid of this!!!!
	virtual const XObject*
	executeXPath(
			const XalanDOMString&	str,
			XalanNode*				contextNode,
			const XalanElement&		resolver);

	virtual const XPath*
	createMatchPattern(
			const XalanDOMString&	str,
			const PrefixResolver&	resolver);

	virtual void
	returnXPath(const XPath*	xpath);

	virtual const XalanDOMString
	evaluateAttrVal(
			XalanNode*				contextNode,
			const PrefixResolver&	namespaceContext,
			const XalanDOMString&	stringedValue);

	virtual void
	pushTopLevelVariables(const ParamVectorType&	topLevelParams);

	virtual const XObject*
	createVariable(
			const ElemTemplateElement*	element,
			const XPath&				xpath,
			XalanNode*					contextNode,
			const PrefixResolver&		resolver);

	virtual const XObject*
	createVariable(
			const ElemTemplateElement*	element,
			const ElemTemplateElement&	templateChild,
			XalanNode*					sourceTree,
			XalanNode*					sourceNode,
			const QName&				mode);

	virtual void
	pushVariable(
			const QName&				name,
			const ElemTemplateElement*	element,
			const XalanDOMString&		str,
			XalanNode*					contextNode,
			const PrefixResolver&		resolver);

	virtual void
	pushVariable(
			const QName&				name,
			const XObject*				var,
			const ElemTemplateElement*	element);

	virtual void
	pushVariable(
			const QName&				name,
			const ElemTemplateElement*	element,
			const XPath&				xpath,
			XalanNode*					contextNode,
			const PrefixResolver&		resolver);

	virtual void
	pushVariable(
			const QName&				name,
			const ElemTemplateElement*	element,
			const ElemTemplateElement&	templateChild,
			XalanNode*					sourceTree,
			XalanNode*					sourceNode);

	virtual void
	pushContextMarker();

	virtual void
	popContextMarker();

	virtual void
	resolveTopLevelParams();

	virtual void
	clearTopLevelParams();

	virtual	void
	pushParams(
			const ElemTemplateElement&	xslCallTemplateElement,
			XalanNode*					sourceTree, 
			XalanNode*					sourceNode,
			const QName&				mode,
			const ElemTemplateElement*	targetTemplate);

	virtual const XObject*
	getParamVariable(const QName&	theName) const;

	virtual void
	pushElementFrame(const ElemTemplateElement*		elem);

	virtual void
	popElementFrame(const ElemTemplateElement*	elem);

	virtual int
	getCurrentStackFrameIndex() const;

	virtual void
	setCurrentStackFrameIndex(int currentStackFrameIndex = -1);

	virtual void
	startDocument();

	virtual void
	endDocument();

	virtual void
	startElement(const XalanDOMChar*	name);

	virtual void
	endElement(const XalanDOMChar*	name);

	virtual void
	characters(
			const XalanDOMChar*		ch,
			unsigned int			start,
			unsigned int			length);

	virtual void
	charactersRaw(
			const XalanDOMChar*		ch,
			unsigned int			start,
			unsigned int			length);

	virtual void
	comment(const XalanDOMChar*		data);

	virtual void
	processingInstruction(
			const XalanDOMChar*		target,
			const XalanDOMChar*		data);

	virtual void
	flushPending();

	virtual void
	cloneToResultTree(
			XalanNode&	node, 
			bool		isLiteral,
			bool		overrideStrip,
			bool		shouldCloneAttributes);

	virtual const XObject*
	createXResultTreeFrag(
			const ElemTemplateElement&	templateChild,
			XalanNode*					sourceTree,
			XalanNode*					sourceNode);

	virtual const XObject*
	createXResultTreeFrag(
			const ElemTemplateElement&	templateChild,
			XalanNode*					sourceTree,
			XalanNode*					sourceNode,
			const QName&				mode);

	virtual bool
	destroyXObject(const XObject*	theXObject) const;

	virtual void
	outputToResultTree(const XObject&	xobj);

	virtual void
	outputResultTreeFragment(const XObject&		theTree);

	virtual const XalanDOMString&
	getXSLNameSpaceURL() const;

	virtual const XalanDOMString&
	getXalanXSLNameSpaceURL() const;

	virtual bool
	findOnElementRecursionStack(const ElemTemplateElement*	theElement) const;

	virtual void
	pushOnElementRecursionStack(const ElemTemplateElement*	theElement);

	virtual const ElemTemplateElement*
	popElementRecursionStack();

	virtual FormatterToXML*
	createFormatterToXML(
			Writer&					writer,
			const XalanDOMString&	version = XalanDOMString(),
			bool					doIndent = false,
			int						indent = 0,
			const XalanDOMString&	encoding = XalanDOMString(),
			const XalanDOMString&	mediaType = XalanDOMString(),
			const XalanDOMString&	doctypeSystem = XalanDOMString(),
			const XalanDOMString&	doctypePublic = XalanDOMString(),
			bool					xmlDecl = true,
			const XalanDOMString&	standalone = XalanDOMString());

	virtual FormatterToHTML*
	createFormatterToHTML(
			Writer&					writer,
			const XalanDOMString&	encoding = XalanDOMString(),
			const XalanDOMString&	mediaType = XalanDOMString(),
			const XalanDOMString&	doctypeSystem = XalanDOMString(),
			const XalanDOMString&	doctypePublic = XalanDOMString(),
			bool					doIndent = true,
			int						indent = 4,
			const XalanDOMString&	version = XalanDOMString(),
			const XalanDOMString&	standalone = XalanDOMString(),
			bool					xmlDecl = false);

	virtual FormatterToDOM*
	createFormatterToDOM(
			XalanDocument*			doc,
			XalanDocumentFragment*	docFrag,
			XalanElement*			currentElement);

	virtual FormatterToDOM*
	createFormatterToDOM(
			XalanDocument*	doc,
			XalanElement*	elem);

	virtual FormatterToText*
	createFormatterToText(Writer&	writer);


	virtual XalanNumberFormatAutoPtr
	createXalanNumberFormat();

	// A basic class to create XalanNumberFormat instances...
	class XALAN_XSLT_EXPORT XalanNumberFormatFactory
	{
	public:

		explicit
		XalanNumberFormatFactory();

		virtual
		~XalanNumberFormatFactory();

		virtual XalanNumberFormat*
		create();
	};

	static XalanNumberFormatFactory&
	getDefaultXalanNumberFormatFactory()
	{
		return s_defaultXalanNumberFormatFactory;
	}

	/**
	 * Static function to install a new XalanNumberFormatFactory.
	 * The caller owns the XalanNumberFormatFactory instance.
	 *
	 * @param a pointer to the new factory instance to use.
	 * @return a pointer to the old factory instance.
	 */
	static XalanNumberFormatFactory*
	installXalanNumberFormatFactory(XalanNumberFormatFactory*	theFactory);


	virtual unsigned long
	getTraceListeners() const;

	virtual void
	fireGenerateEvent(const GenerateEvent&	ge);

	virtual void
	fireTraceEvent(const TracerEvent&	te);

	virtual void
	fireSelectEvent(const SelectionEvent&	se);

	virtual bool
	getTraceSelects() const;

	virtual void
	traceSelect(
			const XalanElement&		theTemplate,
			const NodeRefListBase&	nl) const;

	virtual int
	collationCompare(
			const XalanDOMString&	theLHS,
			const XalanDOMString&	theRHS) const;

	virtual int
	collationCompare(
			const XalanDOMChar*		theLHS,
			const XalanDOMChar*		theRHS) const;

	class XALAN_XSLT_EXPORT CollationCompareFunctor
	{
	public:

		CollationCompareFunctor();

		virtual
		~CollationCompareFunctor();

		virtual int
		operator()(
			const XalanDOMChar*		theLHS,
			const XalanDOMChar*		theRHS) const = 0;
	};

	class XALAN_XSLT_EXPORT DefaultCollationCompareFunctor : public CollationCompareFunctor
	{
	public:

		DefaultCollationCompareFunctor();

		virtual
		~DefaultCollationCompareFunctor();

		virtual int
		operator()(
			const XalanDOMChar*		theLHS,
			const XalanDOMChar*		theRHS) const;
	};

	const CollationCompareFunctor*
	installCollationCompareFunctor(const CollationCompareFunctor*	theFunctor);

	virtual	bool
	getInConstruction(const KeyDeclaration& keyDeclaration) const;

	virtual	void
	beginConstruction(const KeyDeclaration& keyDeclaration);

	virtual	void
	endConstruction(const KeyDeclaration& keyDeclaration);

	// These interfaces are inherited from XPathExecutionContext...

	virtual XalanNode*
	getCurrentNode() const;

	virtual void
	setCurrentNode(XalanNode*	theCurrentNode);

	virtual XObjectFactory&
	getXObjectFactory() const;

	virtual XObject*
	createNodeSet(XalanNode&	theNode);

	virtual bool
	isIgnorableWhitespace(const XalanText&	node) const;

	virtual XalanDOMString
	getNamespaceOfNode(const XalanNode&		n) const;

	virtual XalanDOMString
	getNameOfNode(const XalanNode&	n) const;

	virtual XalanDOMString
	getLocalNameOfNode(const XalanNode&		n) const;

	virtual XalanNode*
	getParentOfNode(const XalanNode&	n) const;

	virtual bool
	isNodeAfter(
			const XalanNode&	node1,
			const XalanNode&	node2) const;

	virtual XalanDOMString
	getNodeData(const XalanNode&	n) const;

	virtual XalanElement*
	getElementByID(
			const XalanDOMString&		id,
			const XalanDocument&		doc) const;

	virtual const NodeRefListBase&
	getContextNodeList() const;

	virtual void	
	setContextNodeList(const NodeRefListBase&	theList);

	virtual unsigned int
	getContextNodeListLength() const;

	virtual unsigned int
	getContextNodeListPosition(const XalanNode&		contextNode) const;

	virtual bool
	elementAvailable(
			const XalanDOMString&	theNamespace, 
			const XalanDOMString&	elementName) const;

	virtual bool
	functionAvailable(
			const XalanDOMString&	theNamespace, 
			const XalanDOMString&	functionName) const;

	virtual XObjectArgVectorType&
	pushArgVector();

	virtual void
	popArgVector();

	virtual const XObject*
	extFunction(
			const XalanDOMString&			theNamespace,
			const XalanDOMString&			functionName,
			XalanNode*						context,
			const XObjectArgVectorType&		argVec);

	virtual XLocator*
	getXLocatorFromNode(const XalanNode*	node) const;

	virtual void
	associateXLocatorToNode(
			const XalanNode*	node,
			XLocator*			xlocator);

	virtual XalanDocument*
	parseXML(
			const XalanDOMString&	urlString,
			const XalanDOMString&	base) const;

	virtual MutableNodeRefList*
	borrowMutableNodeRefList();

	virtual bool
	returnMutableNodeRefList(MutableNodeRefList*	theList);

	virtual MutableNodeRefList*
	createMutableNodeRefList() const;

	virtual bool
	getProcessNamespaces() const;

	virtual const NodeRefListBase*
	getNodeSetByKey(			
			XalanNode*				doc,
			const XalanDOMString&	name,
			const XalanDOMString&	ref,
			const PrefixResolver&	resolver);

	virtual const XObject*
	getVariable(const QName&	name) const;

	virtual const PrefixResolver*
	getPrefixResolver() const;

	virtual void
	setPrefixResolver(const PrefixResolver*		thePrefixResolver);

	virtual XalanDOMString
	getNamespaceForPrefix(const XalanDOMString&		prefix) const;

	virtual XalanDOMString
	findURIFromDoc(const XalanDocument*		owner) const;

	virtual XalanDocument*
	getDOMFactory() const;

	virtual XalanDOMString
	getUnparsedEntityURI(
			const XalanDOMString&	theName,
			const XalanDocument&	theDocument) const;

	virtual bool
	shouldStripSourceNode(const XalanNode&	node);

	virtual bool
	getThrowFoundIndex() const;

	virtual void
	setThrowFoundIndex(bool 	fThrow);

	virtual void
	setCurrentPattern(const XalanDOMString&		thePattern);

	virtual XalanDOMString
	getCurrentPattern() const;

	virtual XalanDocument*
	getSourceDocument(const XalanDOMString&		theURI) const;

	virtual void
	setSourceDocument(
			const XalanDOMString&	theURI,
			XalanDocument*			theDocument);


	virtual const XalanDecimalFormatSymbols*
	getDecimalFormatSymbols(const XalanDOMString&	name);

	virtual PrintWriter*
	createPrintWriter(TextOutputStream*		theTextOutputStream);

	virtual PrintWriter*
	createPrintWriter(
			const XalanDOMString&		theFileName,
			const XalanDOMString&		theEncoding);

	virtual PrintWriter*
#if defined(XALAN_NO_NAMESPACES)
	createPrintWriter(ostream&			theStream);
#else
	createPrintWriter(std::ostream&		theStream);
#endif

	// These interfaces are inherited from StylesheetExecutionContext...

	virtual KeyTable*
	getKeyTable(const XalanNode*	doc) const;

	virtual void
	setKeyTable(
			KeyTable*			keytable,
			const XalanNode*	doc);


	// These interfaces are inherited from ExecutionContext...

	virtual void
	error(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const XalanNode*		styleNode = 0) const;

	virtual void
	warn(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const XalanNode*		styleNode = 0) const;

	virtual void
	message(
			const XalanDOMString&	msg,
			const XalanNode* 		sourceNode = 0,
			const XalanNode*		styleNode = 0) const;

private:

	/**
	 * Pop the top entry from the live variables.
	 */
	void
	popLiveVariablesStack();

	/**
	 * Clear out the entire stack of live variables.
	 */
	void
	clearLiveVariablesStack();

	/**
	 * Determine if the XPath is one that we have cached.
	 *
	 * @param theXPath the XPath instance to check
	 * @return true if the instance has been cached, false if not.
	 */
	bool
	isCached(const XPath*	theXPath);

	/**
	 * Clear out the cache of XPath instances.
	 */
	void
	clearXPathCache();

	/**
	 * Add an XPath instance to the cache, clearing out an old entry
	 * if the cache is full.
	 *
	 * @param pattern the key for looking up the XPath instance in the cache.
	 * @param theXPath the XPath instance to cache
	 */
	void
	addToXPathCache(
			const XalanDOMString&	pattern,
			const XPath*			theXPath);


	XPathExecutionContextDefault	m_xpathExecutionContextDefault;

	// $$ ToDo: Try to remove this dependency, and rely only on XSLTProcessor...
	XSLTEngineImpl&					m_xsltProcessor;

	XalanNode*						m_rootDocument;

#if defined(XALAN_NO_NAMESPACES)
	typedef deque<const ElemTemplateElement*>			ElementRecursionStackType;
	typedef set<FormatterListener*>						FormatterListenerSetType;
	typedef set<PrintWriter*>							PrintWriterSetType;
	typedef set<TextOutputStream*>						TextOutputStreamSetType;
	typedef set<const KeyDeclaration*>					KeyDeclarationSetType;
	typedef vector<const XObject*>						VariablesCollectionType;
	typedef vector<VariablesCollectionType>				LiveVariablesStackType;
	typedef pair<const XPath*, clock_t>					XPathCacheEntry;
	typedef map<XalanDOMString,
				XPathCacheEntry,
				less<XalanDOMString> >					XPathCacheMapType;
#else
	typedef std::deque<const ElemTemplateElement*>		ElementRecursionStackType;
	typedef std::set<FormatterListener*>				FormatterListenerSetType;
	typedef std::set<PrintWriter*>						PrintWriterSetType;
	typedef std::set<TextOutputStream*>					TextOutputStreamSetType;
	typedef std::set<const KeyDeclaration*>				KeyDeclarationSetType;
	typedef std::vector<const XObject*>					VariablesCollectionType;
	typedef std::vector<VariablesCollectionType>		LiveVariablesStackType;
	typedef std::pair<const XPath*, clock_t>			XPathCacheEntry;
	typedef std::map<XalanDOMString, XPathCacheEntry>	XPathCacheMapType;
#endif
	typedef Stylesheet::KeyTablesTableType				KeyTablesTableType;

	enum { eDefaultVariablesCollectionSize = 10,
		   eXPathCacheMax = 50,
		   eDefaultVariablesStackSize = 200 };

	ElementRecursionStackType			m_elementRecursionStack;

	const PrefixResolver*				m_prefixResolver;

	const StylesheetRoot*				m_stylesheetRoot;

	FormatterListenerSetType			m_formatterListeners;

	PrintWriterSetType					m_printWriters;

	TextOutputStreamSetType				m_textOutputStreams;

	const CollationCompareFunctor*		m_collationCompareFunctor;

	LiveVariablesStackType				m_liveVariablesStack;

	/**
	 * Holds all information about variables during execution.
	 */
	VariablesStack						m_variablesStack;

	XPathCacheMapType					m_matchPatternCache;

	KeyTablesTableType					m_keyTables;

	KeyDeclarationSetType				m_keyDeclarationSet;

	static XalanNumberFormatFactory		s_defaultXalanNumberFormatFactory;

	static XalanNumberFormatFactory*	s_xalanNumberFormatFactory;

	const static DefaultCollationCompareFunctor		s_defaultFunctor;
};



#endif	// STYLESHEETEXECUTIONCONTEXTDEFAULT_HEADER_GUARD_1357924680
