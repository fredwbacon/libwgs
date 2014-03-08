VERSION=1.0.0
DOCPATH=User_Manual/publish/en-US/libwgs/$(VERSION)

SOURCES=User_Manual/en-US/User_Manual.xml \
        User_Manual/en-US/Author_Group.xml \
        User_Manual/en-US/Book_Info.xml \
        User_Manual/en-US/Preface.xml \
	User_Manual/en-US/Revision_History.xml \
        User_Manual/en-US/Introduction.xml

manuals: $(SOURCES) api
	@echo -n "Building User Manual..."
	@cd User_Manual; publican build --formats=epub,html,html-desktop,pdf,htmlhelp --langs=en-US --publish
	@cd $(DOCPATH)/htmlhelp/User_Manual/Common_Content/css; cat common.css overrides.css > defaults.css
	@cp User_Manual/book.xml $(DOCPATH)/html/User_Manual/book.xml
	@cp $(DOCPATH)/pdf/User_Manual/libwgs*.pdf libwgs.pdf
	@echo "Done."

api:
	@echo -n "Building api documentation..."
	@doxygen Doxyfile > /dev/null 2>&1
	@mv api/html/libwgs.qch .
	@echo "Done."

clean_ids: clean $(SOURCES)
	cd User_Manual; publican clean_ids

install_book:
	cd User_Manual; publican install_book --site_config ~/Projects/ARISoftware/Documentation/website/aridoc.cfg --lang en-US

.PHONY: clean
clean:
	rm -rf api User_Manual/en-US/*~ 
	cd User_Manual; publican clean

.PHONY: veryclean
veryclean: clean
	rm -rf *.pdf *.chm  *.qch *.tag
