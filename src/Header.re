open Utils;
let styles = requireCSSModule("src/Header.module.css");
let cn = (name) => className(styles, name);

let url = "";
let component = ReasonReact.statelessComponent("Header");
let make = (~pageType, _children) => {
  {
    ...component,
    didMount: (self) => {
      /* Webapi.Dom.(Window.addEventListener("scroll", self.reduce((_) => Scroll), window));
      addEventListener('online', this.handleNetworkChange);
      addEventListener('offline', this.handleNetworkChange);
      this.setState({
        online: navigator.onLine,
      }); */
      ReasonReact.NoUpdate
    },

    render: (_self) =>
      <nav className={cn("header")}>
        <ol className={cn("links")}>
          <li className={cn("logo")}>
            <Link href="/" className="">
              <Logo width="30" height="30" />
            </Link>
          </li>
          <HeaderItem href="/" text="top" url={url} active={pageType == "top"}/>
          <HeaderItem href="/news/1" text="news" url={url} active={pageType == "news"}/>
          <HeaderItem href="/show/1" text="show" url={url} active={pageType == "show"}/>
          <HeaderItem href="/ask/1" text="ask" url={url} active={pageType == "ask"}/>
          <HeaderItem href="/jobs/1" text="jobs" url={url} active={pageType == "jobs"}/>
          <HeaderItem href="/about" text="about" url={url} active={pageType == "about"}/>
        </ol>
      </nav>
  }
};
